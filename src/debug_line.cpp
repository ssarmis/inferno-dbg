#include "general.h"
#include "assert.h"

#include "debug_line.h"

static inline DWARFDebugLineEntry debugLineEntryCreate(DWARFDebugLineStateProgram* program){
    DWARFDebugLineEntry result = {};
    result.address = program->address;
    result.column = program->column;
    result.line = program->line;
    return result;
}

static inline void debugAppendLineEntry(Buffer<DWARFDebugLineEntry>* array, DWARFDebugLineEntry* entry){
    bufferAppend<DWARFDebugLineEntry>(array, entry);
}

static inline void debugAppendFileEntry(Buffer<DWARFDebugFileEntry>* array, DWARFDebugFileEntry* entry){
    bufferAppend<DWARFDebugFileEntry>(array, entry);
}

static inline DWARFDebugLineStateProgram stateProgramCreate(bool defaultStmt){
    DWARFDebugLineStateProgram result = {};

    result.isStmt = defaultStmt;
    result.file = 1;
    result.line = 1;
    result.column = 1;

    return result;
}

static inline DWARFDebugFileEntry readDWARFDebugFileEntry(u8* buffer, u32* offset){
    DWARFDebugFileEntry result = {};
    result.name = readStringFromBuffer(buffer, &result.nameSize, offset);

    // the offset is updated inside readStringFromBuffer
    if(result.nameSize){
        result.directory = readuLEB128FromBuffer(buffer, offset);
        result.xtime = readuLEB128FromBuffer(buffer, offset);
        result.size = readuLEB128FromBuffer(buffer, offset);
    }

    result.array = {};

    return result;
}

Buffer<DWARFDebugFileEntry> debugLineSectionParse(File* file, Elf64_Shdr* sectionHeader, u64 compilationUnitOffset){
    Buffer<DWARFDebugFileEntry> fileEntryTable = {};
    bool good = true;

    u32 offset = sectionHeader->sh_offset + compilationUnitOffset;
    DWARFDebugLine lineInfo;

    lineInfo.length = read64or32BitFromBuffer(file->data, &offset);

    u32 cloneOffset = offset;

    ASSIGN_FROM_FILE((*file), lineInfo.version, u16, offset);
    offset += sizeof(lineInfo.version);
    
    lineInfo.prologueLength = read64or32BitFromBuffer(file->data, &offset);

    ASSIGN_FROM_FILE((*file), lineInfo.minimumInstructionLength, u8, offset);
    offset += sizeof(lineInfo.minimumInstructionLength);
    
    // if(lineInfo.version > 2){
    //     ASSIGN_FROM_FILE((*file), lineInfo.maximumOperationsPerInstruction, u8, offset);
    //     offset += sizeof(lineInfo.maximumOperationsPerInstruction);
    // }

    ASSIGN_FROM_FILE((*file), lineInfo.defaultIsStmt, u8, offset);
    offset += sizeof(lineInfo.defaultIsStmt);
    
    ASSIGN_FROM_FILE((*file), lineInfo.lineBase, i8, offset);
    offset += sizeof(lineInfo.lineBase);

    ASSIGN_FROM_FILE((*file), lineInfo.lineRange, u8, offset);
    offset += sizeof(lineInfo.lineRange);

    ASSIGN_FROM_FILE((*file), lineInfo.opCodeBase, u8, offset);
    offset += sizeof(lineInfo.opCodeBase);

    DTRACE("Length %d\n", lineInfo.length);
    DTRACE("Version %d\n", lineInfo.version);
    DTRACE("Prologue Length %d\n", lineInfo.prologueLength);
    DTRACE("Min Instruction Length %d\n", lineInfo.minimumInstructionLength);
    DTRACE("Default Is Stmt %d\n", lineInfo.defaultIsStmt);
    DTRACE("Line Base %d\n", lineInfo.lineBase);
    DTRACE("Line Range %d\n", lineInfo.lineRange);
    DTRACE("Op Code Base %d\n", lineInfo.opCodeBase);
    // TODO(Sarmis) wrap these into section structs
    // to read nicely from a struct that keeps track of
    // where we are in the section, where the section is, etc
    // offset += sizeof(DWARFDebugLine);

    u8 lengths[255];

    if(lineInfo.opCodeBase > 0){
        // first is 1
        for(int i = 1; i < lineInfo.opCodeBase; ++i){
            // ignore these for now
            ASSIGN_FROM_FILE((*file), lengths[i], u8, offset);
            ++offset;
        }
    }

    // directory table
    u32 size;
    char* string = readStringFromBuffer(file->data, &size, &offset);
    while(size){
        DTRACE("\t%s\n", string);

        string = readStringFromBuffer(file->data, &size, &offset);
    }

    // file entry
    DWARFDebugFileEntry fileEntry = readDWARFDebugFileEntry(file->data, &offset);
    debugAppendFileEntry(&fileEntryTable, &fileEntry);

    while(fileEntry.nameSize){
        fileEntry = readDWARFDebugFileEntry(file->data, &offset);
        debugAppendFileEntry(&fileEntryTable, &fileEntry);
    }

    for(int i = 0; i < fileEntryTable.currentAmount; ++i){
        fileEntry = fileEntryTable.array[i];
        DTRACE("\t%s %d %d %d\n", fileEntry.name, fileEntry.directory, fileEntry.xtime, fileEntry.size);
    }

    DWARFDebugLineStateProgram program = stateProgramCreate(lineInfo.defaultIsStmt);
    bool done = false;
    while(!program.endSequence){
        if(offset - cloneOffset > sectionHeader->sh_size){
            ERROR("Cannot read next opcode, we are ouside our section offset:%04x section size:%04x", offset, sectionHeader->sh_size);
            good = false;
            break;
        }
        u8 opcode;
        ASSIGN_FROM_FILE((*file), opcode, u8, offset);
        offset += sizeof(opcode);

        if(opcode >= lineInfo.opCodeBase){
            // special opcodes
            u32 lineDifference = program.line;
            u64 addressDifference = program.address;
            u8 adjustedCode = opcode - lineInfo.opCodeBase;
            program.address += adjustedCode / lineInfo.lineRange;
            program.line += (lineInfo.lineBase + (adjustedCode % lineInfo.lineRange)) * lineInfo.minimumInstructionLength;
            program.basicBlock = false;
            lineDifference = program.line - lineDifference;
            addressDifference = program.address - addressDifference;

            DWARFDebugLineEntry lineEntry = debugLineEntryCreate(&program);
            debugAppendLineEntry(&(fileEntryTable.array[program.file - 1].array), &lineEntry);
            
            // DTRACE("[0x%08x] Opcode %d Advance address by %d to %x and line by %d to %d\n", offset-sectionHeader->sh_offset, adjustedCode, addressDifference, program.address, lineDifference, program.line);
        } else {
            // standard opcodes
            switch(opcode){
                case 0: {
                        // extended opcode
                        u8 length = readuLEB128FromBuffer(file->data, &offset);
                        // DTRACE("extended opcode of length: %d\n", length);

                        u8 extendedOpcode;
                        ASSIGN_FROM_FILE((*file), extendedOpcode, u8, offset);
                        offset += sizeof(u8);

                        switch(extendedOpcode){
                            case DW_LNE_end_sequence:{
                                    program = stateProgramCreate(lineInfo.defaultIsStmt);
                                    program.endSequence = true;
                                    
                                    DWARFDebugLineEntry lineEntry = debugLineEntryCreate(&program);
                                    debugAppendLineEntry(&(fileEntryTable.array[program.file - 1].array), &lineEntry);
            
                                    DTRACE("[0x%08x] Extended opcode %d End sequence %s %d %d\n", offset-sectionHeader->sh_offset, extendedOpcode, fileEntryTable.array[program.file].name, program.line, program.column);
                                }
                                break;

                            case DW_LNE_set_address:{
                                    // can join in a single line, but would like to debug the value easier, whatever
                                    u64 operand;
                                    ASSIGN_FROM_FILE((*file), operand, u64, offset);
                                    offset += sizeof(operand);

                                    program.address = operand;
                                    DTRACE("[0x%08x] Extended opcode %d Set address %x %d %d\n", offset-sectionHeader->sh_offset, extendedOpcode, program.address, program.line, program.column);
                                }
                                break;

                            case DW_LNE_define_file:{
                                    fileEntry = readDWARFDebugFileEntry(file->data, &offset);
                                    debugAppendFileEntry(&fileEntryTable, &fileEntry);
                                    DTRACE("[0x%08x] Extended opcode %d Added file entry %s %x %d %d\n", offset-sectionHeader->sh_offset, extendedOpcode, fileEntryTable.array[program.file].name,
                                                                                program.address, program.line, program.column);
                                }
                                break;

                            default:{
                                    DTRACE("Undefined extended opcode met %d\n", extendedOpcode);
                                    // assert(false);
                                    offset += length - 1;
                                }
                                break;
                        }
                    }
                    break;

                case DW_LNS_copy:{
                        DWARFDebugLineEntry lineEntry = debugLineEntryCreate(&program);
                        debugAppendLineEntry(&(fileEntryTable.array[program.file - 1].array), &lineEntry);

                        program.basicBlock = false;
                        DTRACE("[0x%08x] Copy %x %d %d\n", offset-sectionHeader->sh_offset, program.address, program.line, program.column);
                    }
                    break;

                case DW_LNS_advance_pc:{
                        u32 operand = readuLEB128FromBuffer(file->data, &offset) * lineInfo.minimumInstructionLength;
                        program.address += operand;
                        DTRACE("[0x%08x] Advance pc by %u to %x\n", offset-sectionHeader->sh_offset, operand, program.address);
                    }
                    break;
                    
                case DW_LNS_advance_line:{
                        i32 operand = readiLEB128FromBuffer(file->data, &offset) * lineInfo.minimumInstructionLength;
                        u32 debugClone = program.line;
                        program.line += operand;
                        DTRACE("[0x%08x] Advance line by %d to %d\n", offset-sectionHeader->sh_offset, program.line - debugClone, program.line);
                    }
                    break;

                case DW_LNS_set_file:{
                        program.file = readuLEB128FromBuffer(file->data, &offset);
                        DTRACE("[0x%08x] Set file %d %x %d %d\n", offset-sectionHeader->sh_offset, program.file, program.address, program.line, program.column);
                    }
                    break;

                case DW_LNS_set_column: {
                        program.column = readuLEB128FromBuffer(file->data, &offset);
                        DTRACE("[0x%08x] Set column to %d\n", offset-sectionHeader->sh_offset, program.column);
                    }
                    break;

                case DW_LNS_negate_stmt: {
                        program.isStmt = !program.isStmt;
                        DTRACE("[0x%08x] Negate stmt %d\n", offset-sectionHeader->sh_offset, program.isStmt);
                    }
                    break;

                case DW_LNS_set_basic_block: {
                        program.basicBlock = true;
                        DTRACE("[0x%08x] Set basic block %x %d %d\n", offset-sectionHeader->sh_offset, program.address, program.line, program.column);
                    }
                    break;

                case DW_LNS_const_add_pc: {
                        // might just do this by hand since this function I won't recomend
                        // to use in other places, doing is by hand is slighlty faster anyway
                        // not that on our computers the difference in this situation will matter...
                        u32 difference = program.address;
                        u8 adjustedCode = 255 - lineInfo.opCodeBase;
                        program.address += adjustedCode / lineInfo.lineRange;
                        difference = program.address - difference;
                        DTRACE("[0x%08x] Const add pc by %d to %x\n", offset-sectionHeader->sh_offset, difference, program.address);
                    }
                    break;
                
                case DW_LNS_fixed_advance_pc: {
                        u16 operand;
                        ASSIGN_FROM_FILE((*file), operand, i16, offset);
                        offset += sizeof(i16);

                        program.address += operand;
                        DTRACE("[0x%08x] Fixed advance pc to %x\n", offset-sectionHeader->sh_offset, program.address);
                    }
                    break;

                case DW_LNS_set_prologue_end: {
                        // TODO(Sarmis) implement me
                    }
                    break;
                
                case DW_LNS_set_epilogue_begin: {
                        // TODO(Sarmis) implement me
                    }
                    break;

                case DW_LNS_set_isa: {
                        // TODO(Sarmis) add isa register
                        u64 isaValue = readuLEB128FromBuffer(file->data, &offset);
                    }
                    break;

                default: {
                        DTRACE("[0x%08x] Undefined opcode met %d\n", offset-sectionHeader->sh_offset, opcode);
                        assert(false);
                    }
                    break;
            }
        }
    }

    if(!good){
        // clean stuff
        delete[] fileEntryTable.array;
        fileEntryTable.currentAmount;
    }

    return fileEntryTable;
}
