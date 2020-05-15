// g++ -o a gl.cpp imgui*.cpp app.cpp -lSDL2main -lSDL2 -lX11 -lGLU -lGL -lXext -DIMGUI_IMPL_OPENGL_LOADER_CUSTOM="\"gl.h\"" -g; ./a
#include "gl.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include "general.h"
#include "file.h"
#include "debug_line.h"
#include "debug.h"
#include "process.h"

#include <SDL2/SDL.h>

extern Process childProcess;
extern Buffer<DWARFDebugRangeSetEntry> rangeEntries;
/////
// TODO(Sarmis) have all these things niclely layed out into
// already made structures for the thing we exepect or need
// so we don't have to reiterate these
// static inline bool componentGetIsEntryPoint(DWARFCompilationUnitDetail detail){
//     DWARFCompilationUnitDetailComponent component;
//     for(int i = 0; i < detail.components.currentAmount; ++i){
//         component = detail.components.array[i];
//         if(component.attributeType == DW_AT_main_subprogram){
//             return true;
//         }
//     }
//     return false;
// }


/////


static inline void createRegistersWindow(u32 width, u32 height, const char* name){
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
    ImGui::Begin(name, NULL,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

    updateRegisters();
    ImGui::Text("RIP: %08x", childProcess.registers.rip);

    ImGui::End();
}

static inline void createMainWindow(u32 width, u32 height, const char* name, File source, i32 highLightLine=1){
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetColorEditOptions(ImGuiColorEditFlags_RGB);
    ImGui::Begin(name, NULL,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoTitleBar);
    
    for(int i = 0; i < source.lines.currentAmount; ++i){
        // TODO(Sarmis) make this without branches
        if(i == (highLightLine - 1)){
            ImGui::TextColored(ImVec4(1.0f,0.0f,1.0f,1.0f), "%.*s", source.lines.array[i].size, source.lines.array[i].data);
        } else {
            ImGui::Text("%.*s", source.lines.array[i].size, source.lines.array[i].data);
        }
    }

    ImGui::End();
}

static inline void createWindow(u32 width, u32 height, const char* name){
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);
    ImGui::Begin(name, NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

    ImGui::End();
}

static inline i32 getMainCompilationUnitIndex(Buffer<DWARFDebugRangeSetEntry> compilationUnits){
    for(int i = 0; i < compilationUnits.currentAmount; ++i){
        DWARFDebugCompilationUnit compilationUnit = compilationUnits.array[i].compilationUnit;

        for(int ii = 0; ii < compilationUnit.components.currentAmount; ++ii){
            DWARFCompilationUnitDetail detail = compilationUnit.components.array[ii];
            // TODO(Sarmis) seach for main aatribute from DWARF
            if(detail.tagType == DW_TAG_subprogram){
                char* name = componentGetName(detail);
                if(name){
                    if(!strcmp(name, "main") || !strcmp(name, "entry") || !strcmp(name, "_start")){
                        return i;
                    }
                }
            }
        }
    }
    return -1;
}

static inline DWARFCompilationUnitDetail getMainEntryPointSubprogram(DWARFDebugCompilationUnit compilationUnit){
    DWARFCompilationUnitDetail result = {};

    for(int ii = 0; ii < compilationUnit.components.currentAmount; ++ii){
        DWARFCompilationUnitDetail detail = compilationUnit.components.array[ii];
        // TODO(Sarmis) seach for main aatribute from DWARF
        if(detail.tagType == DW_TAG_subprogram){
            char* name = componentGetName(detail);
            if(name){
                if(!strcmp(name, "main") || !strcmp(name, "entry") || !strcmp(name, "_start")){
                    return detail;
                }
            }
        }
    }
    return result;
}

static inline DWARFDebugRangeSetEntry* findRangeSetEntryByAddress(Buffer<DWARFDebugRangeSetEntry>* entries, u64 address){
    DWARFDebugRangeSetEntry* result = NULL;

    for(int i = 0; i < entries->currentAmount; ++i){
        DWARFDebugRangeSetEntry* entry = &entries->array[i];
        for(int ii = 0; ii < entry->ranges.currentAmount; ++ii){
            AddressRange range = entry->ranges.array[ii];
            if(address >= range.low && address < range.high){
                return entry;
            }
        }
    }

    return result;
}

static inline u64 findAddressByLineNumber(DWARFDebugCompilationUnit* compilationUnit, u32 line){
    int address = 0;
    for(int i = 0; i < compilationUnit->fileEntries.currentAmount; ++i){
        DWARFDebugFileEntry fileEntry = compilationUnit->fileEntries.array[i];
        for(int ii = 0; ii < fileEntry.array.currentAmount; ++ii){
            if(fileEntry.array.array[ii].line == line){
                return fileEntry.array.array[ii].address;
            } else if(fileEntry.array.array[ii].line < line){
                address = fileEntry.array.array[ii].address;
            } else if(fileEntry.array.array[ii].line > line){
                return address;
            }
        }
    }
    return address;
}

//TODO(Sarmis) in the future, return a struct with the line number, column and file path
static inline u64 findLineNumberByAddress(DWARFDebugCompilationUnit* compilationUnit, u64 address){
    int line = 0;
    for(int i = 0; i < compilationUnit->fileEntries.currentAmount; ++i){
        DWARFDebugFileEntry fileEntry = compilationUnit->fileEntries.array[i];
        for(int ii = 0; ii < fileEntry.array.currentAmount; ++ii){
            if(fileEntry.array.array[ii].address == address){
                return fileEntry.array.array[ii].line;
            } else if(fileEntry.array.array[ii].address < address){
                line = fileEntry.array.array[ii].line;
            } else if(fileEntry.array.array[ii].address > address){
                return line;
            }
        }
    }
    return line;
}

int main(int argumentsCount, char* arguments[]){
    if(argumentsCount < 2){
        ERROR("At least 2 arguments must be provided.\n");
        return 1;
    }
    initializeDebugStrings(); // remove
    // TODO(Sarmis) move this somewhere else
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Inferno DBG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1);

    initializeGl();
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    rangeEntries = dwarfReadDebugData(arguments[1]);

    bool failedToLoadCompilationUnits = !rangeEntries.currentAmount;

    u32 mainCompilationUnitIndex = getMainCompilationUnitIndex(rangeEntries);

    // TODO(Sarmis) look on how these things should be adjusted
    DWARFDebugCompilationUnit mainCompilationUnit = rangeEntries.array[mainCompilationUnitIndex].compilationUnit;
    DWARFCompilationUnitDetail entryRoutine = getMainEntryPointSubprogram(mainCompilationUnit);
    u64 entryPointLowPC = componentGetLowPC(entryRoutine);

    File file = {};
    u64 line;
    DWARFDebugRangeSetEntry* rangeSetEntry = findRangeSetEntryByAddress(&rangeEntries, entryPointLowPC);

    line = findLineNumberByAddress(&(rangeSetEntry->compilationUnit), entryPointLowPC);
    if(!line){
        ERROR("Could not find line for address ! 0x%08x\n", entryPointLowPC);
    }

    char filename[255];
    sprintf(filename, "%s/%s", compilationUnitGetDirectory(rangeSetEntry->compilationUnit), compilationUnitGetName(rangeSetEntry->compilationUnit));
    TRACE("Main is in %s\n", filename);
    file = fileRead(filename);
#if 1
    char* launchArguments[] = {
        NULL
    };

    launchChildProcess(arguments[1], launchArguments);
    if(childProcess.pid == -1){
        TRACE("Failed to launch child process");
        // TODO(Sarmis) clean enviroment
        return 1;
    }

    TRACE("Create child with pid %d\n", childProcess.pid);
    
    debugWaitForProcessToBeAvailable();
    // breakpoint on entry
    debugSetBreakpoint(&rangeEntries.array[mainCompilationUnitIndex].compilationUnit, entryPointLowPC);
    // debugSetBreakpoint(&rangeEntries.array[mainCompilationUnitIndex].compilationUnit, findAddressByLineNumber(&rangeEntries.array[mainCompilationUnitIndex].compilationUnit, 16));
    debugContinue();
#endif
    u64 opcodes = get64(entryPointLowPC);

    bool done = false;
    
    while(!done){
        DWARFDebugRangeSetEntry* rangeSetEntry = findRangeSetEntryByAddress(&rangeEntries, childProcess.registers.rip);
        if(rangeSetEntry){
            file = rangeSetEntry->file;
            line = findLineNumberByAddress(&(rangeSetEntry->compilationUnit), childProcess.registers.rip);
        }
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch(event.type){
                case SDL_KEYDOWN: {
                        if(event.button.button == SDL_SCANCODE_F5){
                            debugContinue();
                        } else if(event.button.button == SDL_SCANCODE_F10){
                            debugStepLine();
                        } else if(event.button.button == SDL_SCANCODE_F11){
                            debugStepInstruction();
                        }
                    }
                    break;
                case SDL_QUIT:{
                        done = true;
                    }
                    break;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        // ui goes here
        // createFilesWindow(256, 256, "Files", compilationUnits);
        createRegistersWindow(512, 256, "Registers");
        // createWatchWindow(512, 512, "Watch Window");
        // createMemoryWindow(512, 512, "Memory View");
        createMainWindow(io.DisplaySize.x, io.DisplaySize.y, "Source", file, line);

        // fileClose(&file);
        
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);
    }

    for(int i = 0; i < rangeEntries.currentAmount; ++i){
        fileClose(&rangeEntries.array[i].file);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}