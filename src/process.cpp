#include "process.h"
#include "signal_handling.h"
#include "general.h"
#include "debug_info.h"

Process childProcess;
struct sigaction signalChildHandlerStructure = {};

void attach(pid_t pid){
    // TODO(Sarmis) implement me
}

void set64(u64 address, u64 data){
    int status = ptrace(PTRACE_POKETEXT, childProcess.pid, address, data);
    if(status){
        ERROR("Could not poke text with 0x%llx at 0x%llx\n", data, address);
        ERROR("Error: %d\n", errno);
    }
}

u64 get64(u64 address){
    errno = 0;
    u64 result = ptrace(PTRACE_PEEKTEXT, childProcess.pid, address, NULL);
    if(result == -1 && errno != 0){
        ERROR("Could not peek text at 0x%llx\n", address);
        assert(false);
    }
    return result;
}

u8 get8(u64 address){
    return get64(address) & 0xff;
}

void updateRegisters(){
    i32 status = ptrace(PTRACE_GETREGS, childProcess.pid, NULL, &(childProcess.registers));
    if(status == -1){
    }
}

void debugWaitForProcessToBeAvailable(){
    while(!childProcess.available){
        usleep(100);
    }
}

static inline void parseMapsFileForProcess(pid_t pid, u64* map){
    // TODO(Sarmis) implement better parsing, not just reading 16 bytes and
    // assuming its always what we want
    char tmpCmd[128];
    char filename[128];
    sprintf(filename, "/proc/%d/maps", pid);
    sprintf(tmpCmd, "cat /proc/%d/maps", pid);

    File mapsFile = fileRead(filename);

    // read just the first offset
    u8 data[16] = {};
    read(mapsFile.descriptor, data, 16);
    // system(tmpCmd);
    TRACE("%c%c%c%c%c%c%c%c\n",
          data[0], data[1], data[2], data[3],
          data[4], data[5], data[6], data[7]);
    // system(tmpCmd);

    map[EXECUTABLE_BASE_ADDRESS] = readuHexToDec(data);
    TRACE("Process base address %llx\n", map[EXECUTABLE_BASE_ADDRESS]);
    
    fileClose(&mapsFile);
}

void launchChildProcess(const char* filename, char* arguments[]){
    signalChildHandlerStructure.sa_sigaction = signalChildHandler;
    signalChildHandlerStructure.sa_flags = SA_SIGINFO;
    int status = sigaction(SIGCHLD, &signalChildHandlerStructure, NULL);    
    if(status == -1){
        TRACE("Could not set a sginal action on %d", SIGCHLD);
        return;
    }

    childProcess.alive = true;
    childProcess.steppingIsEnabled = false;
    childProcess.available = false;
    childProcess.pid = fork();

    if(childProcess.pid == -1){
        ERROR("Could not execute %s\n", filename);
        return;
    }

    if(!childProcess.pid){
        i32 status = ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        if (status == -1){
            ERROR("Could not enable tracing on child process.");
            exit(1);
        }
        execv(filename, arguments);
    }
    TRACE("Create child with pid %d\n", childProcess.pid);

    debugWaitForProcessToBeAvailable();
    parseMapsFileForProcess(childProcess.pid, childProcess.memoryMap);
}


void debugStepInstruction(){
    childProcess.steppingIsEnabled = true;
    ptrace(PTRACE_SINGLESTEP, childProcess.pid, NULL, NULL);
    childProcess.available = false; // TODO(Sarmis) mutex this
}

// void debugSetBreakpointOnLine(DWARFDebugCompilationUnit* compilationUnit, u32 line){
// }

void debugSetBreakpointUser(DWARFDebugCompilationUnit* compilationUnit, u64 address){
    debugSetBreakpoint(BREAKPOINT_USER, compilationUnit, address);
}

void debugSetBreakpoint(BreakpointType type, DWARFDebugCompilationUnit* compilationUnit, u64 address){
    Breakpoint breakpoint = {};
    breakpoint.type = type;

    u64 offset = childProcess.memoryMap[EXECUTABLE_BASE_ADDRESS];

    breakpoint.address = offset + address;
    errno = 0;
    u8 tmp = get8(breakpoint.address + 1);

    u64 opcodes = 0;
    errno = 0;
    opcodes = get64(breakpoint.address);
    breakpoint.originalMachineCode = opcodes & 0xff;

    u64 interuptMask = ((opcodes >> 8) << 8) | 0xcc;

    set64(breakpoint.address, interuptMask);
    tmp = get8(breakpoint.address);

    tmp = get8(breakpoint.address + 1);

    bufferAppend<Breakpoint>(&compilationUnit->breakpoints, &breakpoint);
}

void debugStepLine(){
    // TODO(Sarmis) what the fuck is this ?
    childProcess.lastSignalStatus = true;
    //

    childProcess.steppingIsEnabled = true;
    debugContinue();
}

void debugContinue(){
    ptrace(PTRACE_CONT, childProcess.pid, NULL, NULL);
    childProcess.available = false; // TODO(Sarmis) mutex this
}

void debugSetBreakpointsOnAllLines(DWARFDebugCompilationUnit* compilationUnit){
    for(int i = 0; i < compilationUnit->fileEntries.currentAmount; ++i){
        DWARFDebugFileEntry fileEntry = compilationUnit->fileEntries.array[i];
        u32 lastLine = 0;
        for(int file = 0; file < fileEntry.array.currentAmount; ++file){
            if(lastLine == fileEntry.array.array[file].line){
                continue;
            }

            lastLine = fileEntry.array.array[file].line;
            debugSetBreakpoint(BREAKPOINT_INTERNAL, compilationUnit, fileEntry.array.array[file].address);
        }
    }
}