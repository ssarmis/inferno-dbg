#pragma once

#include <assert.h>
#include <stdio.h>
#include <elf.h>

#include "debug_abbrev.h"
#include "debug_line.h"

#include "file.h"
#include "general.h"
#include "dwarf.h"

#ifndef DEBUG_DWARF_INFO_SECTION
#define DTRACE(...)
#else
#undef DTRACE
#define DTRACE(...) TRACE(__VA_ARGS__)
#endif

struct DWARFDebugCompilationUnitHeader {
    u64 length;
    u16 version;
    u64 debugAbbrevOffset;
    u8 addressSize;
    u32 startingOffset;
    DWARFDebugAbbreviationTable abbreviationTable;
};

struct DWARFCompilationUnitDetailComponent {
    u8 attributeType;
    union {
        bool flagPresent; // DW_FORM_flag_present
        char* name; // FORM_strp or FORM_string

        u8 referenceOffset8; // ref1
        u16 referenceOffset16; // ref2
        u32 referenceOffset32; // ref4
        u64 referenceOffset64; // ref8

        u8 data8; // FORM_data1
        u16 data16; // FORM_data2
        u32 data32; // FORM_data4
        u64 data64; // FORM_data8

        i32 sdata; // FORM_sdata
        u32 udata; // FORM_udata

        u64 address;
        // TODO(Sarmis) implement more forms as new dwarf standard versions come out
        // but mostly probably this much is ok
    };
};

struct DWARFCompilationUnitDetail {
    u8 tagType; // DW_TAG
    Buffer<DWARFCompilationUnitDetailComponent> components;
};

struct DWARFDebugCompilationUnit {
    u64 offsetInSection;
    DWARFDebugCompilationUnitHeader header;
    Buffer<DWARFCompilationUnitDetail> components;
    Buffer<DWARFDebugFileEntry> fileEntries;
    Buffer<Breakpoint> breakpoints;
};

Buffer<DWARFDebugCompilationUnit> debugInfoSectionParse(File* file, Elf64_Shdr* sections);

static inline DWARFDebugCompilationUnit debugInfoGetCompilationUnitByOffset(Buffer<DWARFDebugCompilationUnit>* compilationUnits, u64 offset){
    DWARFDebugCompilationUnit result = {};

    for(int i = 0; i < compilationUnits->currentAmount; ++i){
        if(compilationUnits->array[i].offsetInSection == offset){
            return compilationUnits->array[i];
        }
    }
    return result;
}

static inline char* componentCompilationDirectory(DWARFCompilationUnitDetail detail){
    DWARFCompilationUnitDetailComponent component;
    for(int i = 0; i < detail.components.currentAmount; ++i){
        component = detail.components.array[i];
        if(component.attributeType == DW_AT_comp_dir){
            return component.name;
        }
    }
    return NULL;
}

static inline char* componentGetName(DWARFCompilationUnitDetail detail){
    DWARFCompilationUnitDetailComponent component;
    for(int i = 0; i < detail.components.currentAmount; ++i){
        component = detail.components.array[i];
        if(component.attributeType == DW_AT_name){
            return component.name;
        }
    }
    return NULL;
}

static inline u64 componentGetLowPC(DWARFCompilationUnitDetail detail){
    DWARFCompilationUnitDetailComponent component;
    for(int i = 0; i < detail.components.currentAmount; ++i){
        component = detail.components.array[i];
        if(component.attributeType == DW_AT_low_pc){
            return component.address;
        }
    }
    return 0;
}

static inline u64 componentGetHighPC(DWARFCompilationUnitDetail detail){
    DWARFCompilationUnitDetailComponent component;
    for(int i = 0; i < detail.components.currentAmount; ++i){
        component = detail.components.array[i];
        if(component.attributeType == DW_AT_high_pc){
            return component.address;
        }
    }
    return 0;
}

static inline char* compilationUnitGetName(DWARFDebugCompilationUnit compilationUnit){
    Buffer<DWARFCompilationUnitDetail> components = compilationUnit.components;
    
    DWARFCompilationUnitDetail component;
    for(int i = 0; i < components.currentAmount; ++i){
        component = components.array[i];
        if(component.tagType == DW_TAG_compile_unit){
            return componentGetName(component);
        }
    }
    return NULL;
}

static inline char* compilationUnitGetDirectory(DWARFDebugCompilationUnit compilationUnit){
    Buffer<DWARFCompilationUnitDetail> components = compilationUnit.components;
    
    DWARFCompilationUnitDetail component;
    for(int i = 0; i < components.currentAmount; ++i){
        component = components.array[i];
        if(component.tagType == DW_TAG_compile_unit){
            return componentCompilationDirectory(component);
        }
    }
    return NULL;
}

