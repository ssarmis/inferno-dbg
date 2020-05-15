#include "process.h"
#include "signal_handling.h"
#include "general.h"
#include "debug_info.h"

Process childProcess;
struct sigaction signalChildHandlerStructure = {};

void attach(pid_t pid){
    // TODO(Sarmis) implement me
}

void set64(u64 address, u64 data){
    int status = ptrace(PTRACE_POKETEXT, childProcess.pid, address, data);
    if(status){
        ERROR("Could not poke text with 0x%08x at 0x%08x\n", data, address);
        ERROR("Error: %d\n", errno);
    }
}

u64 get64(u64 address){
    return ptrace(PTRACE_PEEKTEXT, childProcess.pid, address, NULL);
}

u8 get8(u64 address){
    return get64(address) & 0xff;
}

void updateRegisters(){
    i32 status = ptrace(PTRACE_GETREGS, childProcess.pid, NULL, &(childProcess.registers));
    if(status == -1){
    }
}

void debugWaitForProcessToBeAvailable(){
    while(!childProcess.available){
        usleep(100);
    }
}

void launchChildProcess(const char* filename, char* arguments[]){
    signalChildHandlerStructure.sa_sigaction = signalChildHandler;
    signalChildHandlerStructure.sa_flags = SA_SIGINFO;
    int status = sigaction(SIGCHLD, &signalChildHandlerStructure, NULL);    
    if(status == -1){
        TRACE("Could not set a sginal action on %d", SIGCHLD);
        return;
    }

    fflush(stdout);
    childProcess.available = false;
    childProcess.pid = fork();

    if(childProcess.pid == -1){
        ERROR("Could not execute %s\n", filename);
        return;
    }

    if(!childProcess.pid){
        i32 status = ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        if (status == -1){
            ERROR("Could not enable tracing on child process.");
            exit(1);
        }
        execv(filename, arguments);
    }
}


void debugStepInstruction(){
    ptrace(PTRACE_SINGLESTEP, childProcess.pid, NULL, NULL);
    childProcess.available = false; // TODO(Sarmis) mutex this
}

// void debugSetBreakpointOnLine(DWARFDebugCompilationUnit* compilationUnit, u32 line){
// }

void debugSetBreakpoint(DWARFDebugCompilationUnit* compilationUnit, u64 address){
    Breakpoint breakpoint = {};
    // TODO(Sarmis) fix EIO problems with PEEKTEXT into virtual address space
    // for now this is only on Ubuntu, its working fine on Fedora 28
    breakpoint.address = address;
    errno = 0;
    ERROR("Error? %d\n", errno);
    u8 tmp = get8(breakpoint.address + 1);
    TRACE("Next byte code 0x%08x from address 0x%08x\n", tmp, breakpoint.address + 1);
    ERROR("Error? %d\n", errno);

    u64 opcodes = 0;
    errno = 0;
    ERROR("Error? %d\n", errno);
    opcodes = get64(address);
    ERROR("Error? %d\n", errno);
    breakpoint.originalByteCode = opcodes & 0xff;
    TRACE("Original byte code 0x%08x from address 0x%08x\n", opcodes, breakpoint.address);

    u64 interuptMask = ((opcodes >> 8) << 8) | 0xcc;

    set64(address, interuptMask);
    tmp = get8(address);
    TRACE("New byte code 0x%08x from address 0x%08x\n", tmp, breakpoint.address);

    tmp = get8(breakpoint.address + 1);
    TRACE("Next byte code 0x%08x from address 0x%08x\n", tmp, breakpoint.address + 1);

    bufferAppend<Breakpoint>(&compilationUnit->breakpoints, &breakpoint);
}

void debugStepLine(/*, u64 line */){
    // TODO(Sarmis) Implement me
}

void debugContinue(){
    ptrace(PTRACE_CONT, childProcess.pid, NULL, NULL);
    childProcess.available = false; // TODO(Sarmis) mutex this
}