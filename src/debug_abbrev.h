#pragma once

#include <assert.h>
#include <stdio.h>
#include <elf.h>

#include "debug_abbrev.h"

#include "file.h"
#include "general.h"
#include "dwarf.h"

#ifndef DEBUG_DWARF_ABBREV_SECTION
#define DTRACE(...)
#else
#undef DTRACE
#define DTRACE(...) TRACE(__VA_ARGS__)
#endif

struct DWARFDebugAttribute {
    u8 type;
    u8 form;
};

struct DWARFDebugTagEntry {
    u8 tag;
    bool hasChildren;
    Buffer<DWARFDebugAttribute> attributes;
};

struct DWARFDebugAbbreviationTable {
    u64 offsetInDebugAbbreviation;
    Buffer<DWARFDebugTagEntry> tags;
};

DWARFDebugAbbreviationTable debugAbbreviationSectionParse(File* file, Elf64_Shdr* sectionHeader, u32 compilationUnitOffset);