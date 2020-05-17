#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>

#include "general.h"

struct String {
    u8* data;
    u32 size;
};

struct File {
    i64 descriptor;
    i64 size;
    u32 read;
    u8* data;
    Buffer<String> lines;
};

static inline void fileClose(File* file){
    if(file->data){
        delete[] file->data;
        delete[] file->lines.array;
        file->size = 0;
        file->data = NULL;
        file->lines.capacity = 0;
        file->lines.currentAmount = 0;
        file->lines.array = NULL;
    }
    close(file->descriptor);
}

// A returned file with data = NULL means something failed inside the reading routine
static inline File fileRead(const char* filename){
    File result = {};
    result.descriptor = open(filename, O_RDONLY);
    if(result.descriptor < 0){
        ERROR("Could not open file %s\n", filename);
        result.data = NULL;
        return result;
    }

    errno = 0;
    result.size = lseek64(result.descriptor, 0, SEEK_END);
    if(!result.size){
        ERROR("Could not get size of file %s, error %d\n", filename, errno);
        result.data = NULL;
        fileClose(&result);
        return result;
    }    

    if(result.size == -1){
        TRACE("File does not have a set size(might be generated on the fly)\n");
    } else {
        lseek64(result.descriptor, 0, SEEK_SET);

        result.data = new u8[result.size];
        if(!result.data){
            ERROR("Could not allocate size %d for file %s", result.size, filename);
            fileClose(&result);
            return result;
        }

        u32 readBytes = 0;
        u32 bytes = 0;
        while((bytes = read(result.descriptor, result.data, result.size))){
            readBytes += bytes;
        }

        if(readBytes != result.size){
            ERROR("Could not read entire size from file %s", filename);
            result.data = NULL;
            fileClose(&result);
            return result;
        }    

        // read lines
        // TODO(Sarmis) reimplement this
        u8* iterator = result.data;
        String string = {};
        u8* checkpoint = NULL;
        while(iterator - result.data <= result.size){
            if(*iterator == '\n' || *iterator == '\r' || !(*iterator)){
                if(string.size > 0){
                    bufferAppend<String>(&(result.lines), &string);
                }
                string.data = iterator;
                string.size = 1;
                checkpoint = NULL;
            } else {
                if(!checkpoint){
                    checkpoint = iterator;
                    string.data = iterator;
                }
                ++string.size;
            }
            ++iterator;
        }
    }
    return result;
}

#define ASSIGN_FROM_FILE(file, destination, type, offset){\
    assert(file.size != file.read);\
    if(!(offset)){\
        ASSIGN_FROM_BUFFER((file.data + file.read), (destination), type);\
        file.read += sizeof(type);\
    } else {\
        ASSIGN_FROM_BUFFER((file.data + (offset)), (destination), type);\
    }\
}
