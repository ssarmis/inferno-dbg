#include "general.h"
#include "debug_info.h"
#include "debug_line.h"
#include "debug_abbrev.h"

static inline void debugAppendCompilationUnitDetail(DWARFCompilationUnitDetail* componentDetail, DWARFCompilationUnitDetailComponent* component){
    bufferAppend<DWARFCompilationUnitDetailComponent>(&(componentDetail->components), component);
}

Buffer<DWARFDebugCompilationUnit> debugInfoSectionParse(File* file, Elf64_Shdr* sections){
#ifdef DEBUG_DWARF_INFO_SECTION
    initializeDebugStrings();
#endif
    Buffer<DWARFDebugCompilationUnit> compilationUnits = {};

    Elf64_Shdr sectionHeader = sections[SECTION_DEBUG_INFO];
    Elf64_Shdr stringSectionHeader = sections[SECTION_DEBUG_STRING];

    u32 offset = sectionHeader.sh_offset;
    bool good = true;
    u32 offstInSectionClone = offset;
    
    Buffer<DWARFDebugAbbreviationTable> cachedAbbriviationTables = {};

    while(offset - offstInSectionClone < sectionHeader.sh_size){
        DWARFDebugCompilationUnit compilationUnit = {};
        // since the offsets or lengths can be either 64bit or 32bit, 
        // doesn't matter thats a x86_64, we can't consume the whole header
        // in one go smoothly

        // component unit header
        // TODO(Sarmis) move into its own function
        compilationUnit.offsetInSection = offset - offstInSectionClone;
        compilationUnit.header.length = read64or32BitFromBuffer(file->data, &offset);
        if(!compilationUnit.header.length){
            break;
        }
        u32 offsetClone = offset;

        ASSIGN_FROM_FILE((*file), compilationUnit.header.version, u16, offset);
        offset += sizeof(compilationUnit.header.version);

        compilationUnit.header.debugAbbrevOffset = read64or32BitFromBuffer(file->data, &offset);
        DWARFDebugAbbreviationTable abbreviationTable = {};
        
        bool cached = false;
        for(int i = 0; i < cachedAbbriviationTables.currentAmount; ++i){
            if(cachedAbbriviationTables.array[i].offsetInDebugAbbreviation == compilationUnit.header.debugAbbrevOffset){
                abbreviationTable = cachedAbbriviationTables.array[i];
                cached = true;
                break;
            }
        }

        if(!cached){
            abbreviationTable = debugAbbreviationSectionParse(file, &sections[SECTION_DEBUG_ABBREV], compilationUnit.header.debugAbbrevOffset);
            bufferAppend<DWARFDebugAbbreviationTable>(&cachedAbbriviationTables, &abbreviationTable);
        }

        ASSIGN_FROM_FILE((*file), compilationUnit.header.addressSize, u8, offset);
        offset += sizeof(compilationUnit.header.addressSize);

        bool validAddressSize = (compilationUnit.header.addressSize == 8) || (compilationUnit.header.addressSize == 4);
        if(!validAddressSize){
            ERROR("Invalid address size in .debug_info\n");
            compilationUnits = {};
            return compilationUnits;
        }

        DTRACE("===========================\n");
        DTRACE("Offset: 0x%08x\n", compilationUnit.header.debugAbbrevOffset);
        DTRACE("Length: 0x%08x\n", compilationUnit.header.length);
        DTRACE("Version: %d\n", compilationUnit.header.version);
        DTRACE("Address size: %d\n", compilationUnit.header.addressSize);
        DTRACE("===========================\n");
        ////
        u32 abbreviationCode;
        while(offset - offsetClone < compilationUnit.header.length){
            DWARFCompilationUnitDetail componenentDetail = {};

            abbreviationCode = readuLEB128FromBuffer((*file).data, &offset);
            DTRACE("Abbreviation %d\n", abbreviationCode);
            if(!abbreviationCode){
                continue;
            }
            DWARFDebugTagEntry tag = abbreviationTable.tags.array[abbreviationCode - 1];
            componenentDetail.tagType = tag.tag;
            // TODO(Sarmis) use the child attribute to create a tree for faster search ?

            DTRACE("\n%s:\n", dwarfTagsStrings[tag.tag]);
            DTRACE("\t\tChild %d\n", tag.hasChildren);
            bool isCompilationUnitTag = tag.tag == DW_TAG_compile_unit;
            bool parseDebugLineStatements = false;

            DWARFDebugAttribute attribute;
            for(int i = 0; i < tag.attributes.currentAmount; ++i){
                DWARFCompilationUnitDetailComponent component = {};
                attribute = tag.attributes.array[i];

                component.attributeType = attribute.type;

                DTRACE("\t%s %30s\n", dwarfAttributeStrings[attribute.type], dwarfFormStrings[attribute.form]);
                if(isCompilationUnitTag){
                    if(attribute.type == DW_AT_stmt_list){
                        parseDebugLineStatements = true;
                    }
                }

                switch(attribute.form){
                    case DW_FORM_exprloc:{
                            u32 length = readuLEB128FromBuffer(file->data, &offset);
                            // implement me
                            offset += length;
                        }
                        break;

                    case DW_FORM_flag_present:{
                            component.flagPresent = true;
                            DTRACE("\t\tflag presentx\n");
                        }
                        break;

                    case DW_FORM_ref1:{
                            ASSIGN_FROM_FILE((*file), component.referenceOffset8, u8, offset);
                            offset += sizeof(u8);
                            DTRACE("\t\t0x%08x\n", component.referenceOffset8);
                        }
                        break;

                    case DW_FORM_ref2:{
                            ASSIGN_FROM_FILE((*file), component.referenceOffset16, u16, offset);
                            offset += sizeof(u16);
                            DTRACE("\t\t0x%08x\n", component.referenceOffset16);
                        }
                        break;

                    case DW_FORM_ref4:{
                            ASSIGN_FROM_FILE((*file), component.referenceOffset32, u32, offset);
                            offset += sizeof(u32);
                            DTRACE("\t\t0x%08x\n", component.referenceOffset32);
                        }
                        break;

                    case DW_FORM_ref8:{
                            ASSIGN_FROM_FILE((*file), component.referenceOffset64, u64, offset);
                            offset += sizeof(u64);
                            DTRACE("\t\t0x%08x\n", component.referenceOffset64);
                        }
                        break;

                    case DW_FORM_ref_addr:{
                            // TODO(Sarmis) review this, was this meant to be a hardcoded address
                            // or just an offset like the others
                            component.referenceOffset64 = read64or32BitFromBuffer(file->data, &offset);
                            DTRACE("\t\t0x%08x\n", component.referenceOffset64);
                        }
                        break;

                    case DW_FORM_sec_offset:{
                            // could be usefull if we remake the linking
                            // with the debug line section to put everything
                            // in the compilation units more nicely
                            // I will be lazy for now
                            u64 stmtOffsetInDebugLine = read64or32BitFromBuffer(file->data, &offset);
                            DTRACE("\t\t0x%08x\n", stmtOffsetInDebugLine);
                            // TODO(Sarmis) move this into a routine where we analyze
                            // the attributes from this "info" section
                            if(parseDebugLineStatements){
                                compilationUnit.fileEntries = debugLineSectionParse(file, &sections[SECTION_DEBUG_LINE], stmtOffsetInDebugLine);
                            }
                            parseDebugLineStatements = false;
                        }
                        break;

                    case DW_FORM_addr:{
                            if(compilationUnit.header.addressSize == 8){
                                ASSIGN_FROM_FILE((*file), component.address, u64, offset);
                                offset += sizeof(u64);
                            }  else if(compilationUnit.header.addressSize == 4){
                                ASSIGN_FROM_FILE((*file), component.address, u32, offset);
                                offset += sizeof(u32);
                            }
                            DTRACE("\t\t0x%08x\n", component.address);
                        }
                        break;

                    case DW_FORM_data1:{
                            ASSIGN_FROM_FILE((*file), component.data8, u8, offset);
                            offset += sizeof(u8);
                            DTRACE("\t\t%d\n", component.data8);
                        }
                        break;

                    case DW_FORM_data2:{
                            ASSIGN_FROM_FILE((*file), component.data16, u16, offset);
                            offset += sizeof(u16);
                            DTRACE("\t\t%d\n", component.data16);
                        }
                        break;

                    case DW_FORM_data4:{
                            ASSIGN_FROM_FILE((*file), component.data32, u32, offset);
                            offset += sizeof(u32);
                            DTRACE("\t\t%d\n", component.data32);
                        }
                        break;

                    case DW_FORM_data8:{
                            ASSIGN_FROM_FILE((*file), component.data64, u64, offset);
                            offset += sizeof(u64);
                            DTRACE("\t\t%d\n", component.data64);
                        }
                        break;

                    case DW_FORM_sdata: {
                            component.sdata = readiLEB128FromBuffer(file->data, &offset);
                            DTRACE("\t\t%d\n", component.sdata);
                        }
                        break;

                    case DW_FORM_udata: {
                            component.udata = readuLEB128FromBuffer(file->data, &offset);
                            DTRACE("\t\t%d\n", component.udata);
                        }
                        break;

                    case DW_FORM_strp:{
                            u64 stringPointer = read64or32BitFromBuffer(file->data, &offset);
                            // TODO(Sarmis) change read string form buffer to take a 64bit offset
                            u32 finalOffset = stringSectionHeader.sh_offset + stringPointer;
                            component.name = readStringFromBuffer(file->data, NULL, &finalOffset);
                            DTRACE("\t\t[offset: 0x%08x]%s\n", stringPointer, component.name);
                        }
                        break;

                    case DW_FORM_string:{
                            component.name = readStringFromBuffer(file->data, NULL, &offset);
                            DTRACE("\t\t%s\n", component.name);
                        }
                        break; 
                    
                    default: {
                            ERROR("Unimplemented form %s was encountered.", dwarfFormStrings[attribute.form]);
                            compilationUnits = {};
                            return compilationUnits;
                        }
                        break;
                }
                debugAppendCompilationUnitDetail(&componenentDetail, &component);
            }
            bufferAppend<DWARFCompilationUnitDetail>(&(compilationUnit.components), &componenentDetail);    
        }
        bufferAppend<DWARFDebugCompilationUnit>(&compilationUnits, &compilationUnit);
    }

    return compilationUnits;
}
