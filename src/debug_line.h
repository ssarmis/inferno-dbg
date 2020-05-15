#pragma once

#include <assert.h>
#include <stdio.h>
#include <elf.h>

#include "file.h"
#include "general.h"
#include "dwarf.h"

#ifndef DEBUG_DWARF_LINE_SECTION
#define DTRACE(...)
#else
#undef DTRACE
#define DTRACE(...) TRACE(__VA_ARGS__)
#endif

#pragma pack(push, 1)
struct DWARFDebugLine {
    u64 length;
    u16 version;
    u64 prologueLength;
    u8 minimumInstructionLength;
    u8 maximumOperationsPerInstruction;
    u8 defaultIsStmt;
    i8 lineBase;
    u8 lineRange;
    u8 opCodeBase;
};
#pragma pack(pop)

struct DWARFDebugLineEntry {
    u64 address;
    u32 line;
    u32 column;
};

struct DWARFDebugFileEntry {
    char* name;
    u32 nameSize;
    u32 directory;
    u32 xtime;
    u32 size;
    Buffer<DWARFDebugLineEntry> array;
};

struct DWARFDebugLineStateProgram {
    u64 address;
    u32 file;
    u32 line;
    u32 column;
    bool isStmt;
    bool basicBlock;
    bool endSequence;
};

Buffer<DWARFDebugFileEntry> debugLineSectionParse(File* file, Elf64_Shdr* sectionHeader, u64 compilationUnitOffset);

