#pragma once

#include <elf.h>
#include "dwarf.h"
#include "debug_info.h"
#include "file.h"

#pragma pack(push, 1)
struct DWARFArangesHeader {
    u32 length;
    u16 version;
    u32 infoOffset;
    u8 addressSize;
    u8 segmentDescriptorSize;
};
#pragma pack(pop)

struct AddressRange {
    u64 low;
    u64 high;
};

struct DWARFDebugRangeSetEntry {
    DWARFDebugCompilationUnit compilationUnit;
    Buffer<AddressRange> ranges;
    File file;
};

static inline Buffer<DWARFDebugRangeSetEntry> debugArangesSectionParse(File* file, Elf64_Shdr* sections, Buffer<DWARFDebugCompilationUnit>* compilationUnits){
    Buffer<DWARFDebugRangeSetEntry> result = {};

    Elf64_Shdr sectionHeader = sections[SECTION_DEBUG_ARANGES];

    u32 offset = sectionHeader.sh_offset;
    u32 offsetClone = offset;
    while(offset - offsetClone < sectionHeader.sh_size){
        DWARFDebugRangeSetEntry entry = {};

        u32 paddingOffset = offset;
        DWARFArangesHeader header;

        ASSIGN_FROM_FILE((*file), header, DWARFArangesHeader, offset);
        offset += sizeof(DWARFArangesHeader);

        DTRACE("============================\n");
        DTRACE("Length: %d\n", header.length);
        DTRACE("Versin: %d\n", header.version);
        DTRACE("Info Offset: 0x%08x\n", header.infoOffset);
        DTRACE("Address Size: %d\n", header.addressSize);
        DTRACE("Segment Descriptor Size: %d\n", header.segmentDescriptorSize);
        DTRACE("============================\n");

        if(!header.length && !header.version){
            break;
        }

        if(!header.length){
            // put back what was read in addition
            offset -= sizeof(DWARFArangesHeader) - sizeof(header.length);
            continue;
        }

        if(header.addressSize != 8 && header.addressSize != 4){
            ERROR("Address is neither of the valid values (4, 8).\n");
            break;
        }

        entry.compilationUnit = debugInfoGetCompilationUnitByOffset(compilationUnits, header.infoOffset);
        char filename[255];
        sprintf(filename, "%s/%s", compilationUnitGetDirectory(entry.compilationUnit), compilationUnitGetName(entry.compilationUnit));
        entry.file = fileRead(filename);

        u32 offsetBeforePadding = offset;
        paddingOffset = offset - paddingOffset;
        
        while(paddingOffset % (header.addressSize*2)){
            ++paddingOffset;
            ++offset;
        }

        u32 padding = (offset - offsetBeforePadding);
        u32 bytesRead = sizeof(DWARFArangesHeader) - sizeof(header.length) + padding;

        u64 address;
        u64 length;
        while(bytesRead < header.length){
            AddressRange range = {};
            // TODO(Sarmis) don't hardcode these for 4, 8, read the actual
            // amount of bytes instead
            if(header.addressSize == 4){
                ASSIGN_FROM_FILE((*file), address, u32, offset);
                offset += sizeof(u32);

                ASSIGN_FROM_FILE((*file), length, u32, offset);
                offset += sizeof(u32);
            } else if(header.addressSize == 8){
                ASSIGN_FROM_FILE((*file), address, u64, offset);
                offset += sizeof(u64);

                ASSIGN_FROM_FILE((*file), length, u64, offset);
                offset += sizeof(u64);
            }

            bytesRead += header.addressSize * 2;
            range.low = address;
            range.high = address + length;
            bufferAppend<AddressRange>(&(entry.ranges), &range);

            DTRACE("0x%08x 0x%08x\n", address, length);
        }
        bufferAppend<DWARFDebugRangeSetEntry>(&result, &entry);
    }
    
    return result;
}