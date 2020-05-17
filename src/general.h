#pragma once
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef float r32;
typedef double r64;

#define TRACE(...) fprintf(stdout, __VA_ARGS__)
#define ERROR(...) fprintf(stderr, __VA_ARGS__)

#define ASSIGN_FROM_BUFFER(source, destination, type){\
    destination = *((type*)(source));\
}

#include <sys/user.h>
#include <unistd.h>

#define EXECUTABLE_BASE_ADDRESS         0
#define EXECUTABLE_BASE_STACK_ADDRESS   1

#define EXECUTABLE_ARRAY_MAXIMUM_SIZE   ((EXECUTABLE_BASE_STACK_ADDRESS) + 1)

struct Process {
    bool alive;
    bool steppingIsEnabled;
    pid_t pid;
    bool available;
    int lastSignalStatus;
    user_regs_struct registers;
    u64 memoryMap[EXECUTABLE_ARRAY_MAXIMUM_SIZE];
};

template<typename T>
struct Buffer {
    u32 currentAmount;
    u32 capacity;
    T* array;
};

template<typename T>
static inline void bufferAppend(Buffer<T>* buffer, T* entry){
    if(!buffer){
        ERROR("Cannot strech buffer of NULL buffer\n");
        assert(false);
    }
    
    if(buffer->currentAmount == buffer->capacity){
        buffer->capacity = (buffer->capacity + 1) * 2;
        T* clone = buffer->array;
        buffer->array = new T[buffer->capacity];
        if(clone){
            for(int i = 0; i < buffer->currentAmount; ++i){
                buffer->array[i] = clone[i];
            }
            delete[] clone;
        }
    }

    buffer->array[buffer->currentAmount] = *entry;
    ++buffer->currentAmount;
}

static inline u8 hexCharToDec(char character){
    // TODO(Sarmis) maybe move to a hardcoded array table
    // faster conversion
    if(character >= 'a' && character <= 'f') {
        return (10 + character - 'a');
    } else if(character >= 'A' && character <= 'F'){
        return (10 + character - 'A');
    }

    // this assumes a valid character in inserted
    return (character - '0');
}

static inline u64 readuHexToDec(u8* buffer){
    u64 result = 0;
    u32 size = 0;
    
    if((buffer[1] == 'x' || buffer[1] == 'X')){
        if(buffer[0] != '0'){
            ERROR("Invalid string, can't parse to dec. \n");
            return -1;
        } else {
            buffer += 2; /*0x*/
        }
    }

    while((*buffer >= 'a' && *buffer <= 'f') ||
          (*buffer >= 'A' && *buffer <= 'F') ||
          (*buffer >= '0' && *buffer <= '9')){
        ++size;
        ++buffer;
        if(size > 16){
            ERROR("Number too big to parse to dec.\n");
            break;
        }
    }

    buffer -= size;

    while(size){
        u64 mask = ((u64)hexCharToDec(*buffer)) << (4 * (--size));
        result |= mask;
        ++buffer;
    }

    return result;
}

static inline char* readStringFromBuffer(u8* buffer, u32* size, u32* offset){
    buffer += *offset;
    char* result = (char*)buffer;
    u32 offsetClone = *offset;

    while(*buffer && 
         ((*buffer >= 'a' && *buffer <= 'z') ||
          (*buffer >= 'A' && *buffer <= 'Z') ||
          (*buffer >= '0' && *buffer <= '9') ||
          (*buffer >= '!' && *buffer <= '/') ||
          (*buffer >= ':' && *buffer <= '@') ||
          (*buffer >= '[' && *buffer <= '`') ||
          (*buffer >= '{' && *buffer <= '~'))){
              

        ++(*offset);
        ++buffer;
    }

    if(size){
        *size = *offset - offsetClone;
        if(!(*size)){
            result = NULL;
        }
    }
    
    // jump over the null terminator
    ++(*offset);

    return result;
}


static inline u32 readLEB128FromBuffer(u8* buffer, u32* offset, bool* signBit=NULL){
    buffer += *offset;

    u32 result = 0;
    u32 bytes = 0;

    while(true){
        if(bytes >= 4){
            ERROR("Could not parse LEB128 bytes because the LEB128 stream has more than 3 bytes, offset(0x%08x).\n", *offset);
            return 0;
        }

        result |= ((buffer[bytes] & 0x7f) << (bytes * 7));

        u8 firstBit = (buffer[bytes] >> 7) & 0x1;
        ++bytes;
        if(!firstBit){
            if((buffer[bytes - 1] & 0x40) && signBit){
                *signBit = true;
            }
            break;
        }
    }

    *offset += bytes;
    return result;
}


static inline i32 readiLEB128FromBuffer(u8* buffer, u32* offset){
    u32 clone = *offset;
    bool signBit = false;
    i32 raw = readLEB128FromBuffer(buffer, offset, &signBit);
    u8 bytes = *offset - clone;

    if(signBit){
        raw |= (~0 << (bytes * 7));
    }
    return raw;
}

static inline u32 readuLEB128FromBuffer(u8* buffer, u32* offset){
    u32 clone = *offset;
    
    u32 result = readLEB128FromBuffer(buffer, offset);
    u8 bytes = *offset - clone;

    u32 mask = ((1 << (bytes * 7)) - 1);
    return (result & mask);
}
