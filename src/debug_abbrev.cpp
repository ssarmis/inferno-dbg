#include "general.h"
#include "debug_abbrev.h"

static inline void debugAppendTags(DWARFDebugAbbreviationTable* table, DWARFDebugTagEntry* entry){
    bufferAppend<DWARFDebugTagEntry>(&(table->tags), entry);
}

static inline void debugAppendAttribute(DWARFDebugTagEntry* entry, DWARFDebugAttribute attribute){
    bufferAppend<DWARFDebugAttribute>(&(entry->attributes), &attribute);
}

DWARFDebugAbbreviationTable debugAbbreviationSectionParse(File* file, Elf64_Shdr* sectionHeader, u32 compilationUnitOffset){
#ifdef DEBUG_DWARF_ABBREV_SECTION
    initializeDebugStrings();
#endif
    DWARFDebugAbbreviationTable result = {};
    result.offsetInDebugAbbreviation = compilationUnitOffset;

    u32 offset = sectionHeader->sh_offset + result.offsetInDebugAbbreviation;
    while(true){
        DWARFDebugTagEntry entry = {};

        // must see if the index is always increasing
        u8 index = readuLEB128FromBuffer(file->data, &offset);
        if(!index){
            break;
        }
        entry.tag = readuLEB128FromBuffer(file->data, &offset);
        DTRACE("%d %s\n", index, dwarfTagsStrings[entry.tag]);

        u8 children;
        ASSIGN_FROM_FILE((*file), children, u8, offset);
        offset += sizeof(children);
        DTRACE("\t%s\n", dwarfChilrenStrings[children]);
        entry.hasChildren = children;

        while(true){
            DWARFDebugAttribute attribute;
            attribute.type = readuLEB128FromBuffer(file->data, &offset);
            attribute.form = readuLEB128FromBuffer(file->data, &offset);
            DTRACE("\t%s %30s\n", dwarfAttributeStrings[attribute.type], dwarfFormStrings[attribute.form]);

            if(!attribute.type){
                if(!attribute.form){
                    break;
                }
                DTRACE("SKipping NULL entry\n");
                continue;
            }

            debugAppendAttribute(&entry, attribute);
        }

        debugAppendTags(&result, &entry);
    }
    return result;
}