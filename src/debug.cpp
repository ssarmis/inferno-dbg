#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <elf.h>
#include <assert.h>
#include <string.h>

#include "general.h"
#include "file.h"

#include "debug_line.h"
#include "debug_info.h"
#include "debug_aranges.h"

Buffer<DWARFDebugRangeSetEntry> rangeEntries;

static inline void handleELFHeader(Elf64_Ehdr* header){
    TRACE("Header\n");
    switch(header->e_type){
        case ET_EXEC: {
                TRACE("\tFile is an executable!\n");
            }
            break;

        default: {
                ERROR("\tELF type unhandled %u\n", header->e_type);
            }
            break;
    }

    switch(header->e_machine){
        case EM_X86_64: {
                TRACE("\tFile is of x86_64 arhitecture!\n");
            }
            break;

        default: {
                ERROR("\tArhitecture type unhandled %d\n", header->e_machine);
            }
            break;
    }
    TRACE("\tSize of sections %d\n", header->e_shentsize);
    TRACE("\tProgram Header of size %d\n", header->e_phentsize);
    TRACE("\tAmount of program headers %d\n", header->e_phnum);
    TRACE("\tAmount of sections in file %d\n", header->e_shnum);
}


Buffer<DWARFDebugRangeSetEntry> dwarfReadDebugData(const char* filename){
    Buffer<DWARFDebugRangeSetEntry> result = {};
    
    File file = fileRead(filename);
    
    if(!file.data){
        ERROR("Something didn't work while opening the executable, exiting.");
        return result;
    }
    // fileClose(&file); // just because we only need to read it, than we can discard it.
    
    Elf64_Ehdr header;
    ASSIGN_FROM_FILE(file, header, Elf64_Ehdr, 0);
    handleELFHeader(&header);

    if(header.e_phoff){
        for(int i = 0; i < header.e_phnum; ++i){
            Elf64_Phdr programHeader;
            ASSIGN_FROM_FILE(file, programHeader, Elf64_Phdr, 0);
            // TRACE("Program Header\n");
            // TRACE("\tShould be loaded %x\n", programHeader.p_type);
            // TRACE("\tPhysical address %x\n", programHeader.p_paddr);
            // TRACE("\tVirtual address %x\n", programHeader.p_vaddr);
            // TRACE("\tAlignment %x\n", programHeader.p_align);
        }
    }

    u64 offsetInSectionTable = header.e_shoff;
    u64 offsetForSectionNames = offsetInSectionTable + header.e_shentsize * (header.e_shnum - 1);
    // peek last section, thats the names
    Elf64_Shdr sectionNames;
    ASSIGN_FROM_FILE(file, sectionNames, Elf64_Shdr, offsetForSectionNames);
    u64 sectionNamesOffset = sectionNames.sh_offset;
    // TRACE("Index in string table %d\n", sectionNames.sh_name);
    // TRACE("Offset of section names %d\n", sectionNamesOffset);

    Elf64_Shdr sections[SECTION_DEBUG_ARRAY_SIZE] = {};

    for(int i = 0; i < header.e_shnum - 1; ++i){
        Elf64_Shdr sectionHeader;
        ASSIGN_FROM_FILE(file, sectionHeader, Elf64_Shdr, offsetInSectionTable);
        offsetInSectionTable += sizeof(Elf64_Shdr);
        char* name = (char*)(file.data + sectionNamesOffset + sectionHeader.sh_name);
        TRACE("%s\n", name);
        TRACE("\tSize: %d\n", sectionHeader.sh_size);
        TRACE("\tOffset: %x\n", sectionHeader.sh_offset);
        // TRACE("\tOffset in file %x\n", sectionHeader.sh_offset);

        if(!strcmp(name, ".debug_line")){
            sections[SECTION_DEBUG_LINE] = sectionHeader;
        } else if(!strcmp(name, ".debug_abbrev")){
            sections[SECTION_DEBUG_ABBREV] = sectionHeader;
        } else if(!strcmp(name, ".debug_info")){
            sections[SECTION_DEBUG_INFO] = sectionHeader;
        } else if(!strcmp(name, ".debug_str")){
            sections[SECTION_DEBUG_STRING] = sectionHeader;
        } else if(!strcmp(name, ".debug_aranges")){
            sections[SECTION_DEBUG_ARANGES] = sectionHeader;
        }
    }

    Buffer<DWARFDebugCompilationUnit> compilationUnits = debugInfoSectionParse(&file, sections);
    if(!compilationUnits.currentAmount){
        ERROR("Something went wrong with reading the .debug_info sectiom, exiting.\n");
        // clear enviroment
        fileClose(&file);
        return result;
    }

    result = debugArangesSectionParse(&file, sections, &compilationUnits);
    
    return result;
}