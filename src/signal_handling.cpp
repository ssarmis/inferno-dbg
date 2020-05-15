#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <pthread.h>

#include "general.h"
#include "process.h"
#include "signal_handling.h"
#include "debug_aranges.h"

extern Buffer<DWARFDebugRangeSetEntry> rangeEntries;

static inline Breakpoint* breakpointGetByAddress(DWARFDebugCompilationUnit* compilationUnit, u64 address){
    Breakpoint* result = NULL;
    for(int i = 0; i < compilationUnit->breakpoints.currentAmount; ++i){
        if(compilationUnit->breakpoints.array[i].address == address){
            return &compilationUnit->breakpoints.array[i];
        }
    }
    return result;
}

void signalChildHandler(int signalNumber, siginfo_t* signalInfo, void/* ucontext_t */* context){
    TRACE("Received signal %d %08x\n", signalNumber, signalInfo->si_errno);

    switch(signalInfo->si_code){
        case CLD_TRAPPED:{
                TRACE("The child is trapped! %d\n", signalInfo->si_status);
                int signalStatus = signalInfo->si_status;
                if(WIFSIGNALED(signalStatus)){
                    switch (WTERMSIG(signalStatus)){
                        case SIGSEGV:{
                                TRACE("Program ended in segmentation fault\n");
                            }
                            break;
                    }
                }

                Breakpoint* currentHitBreakpoint;
                ptrace(PTRACE_GETREGS, childProcess.pid, NULL, &childProcess.registers);
                for(int i = 0; i < rangeEntries.currentAmount; ++i){
                    currentHitBreakpoint = breakpointGetByAddress(&rangeEntries.array[i].compilationUnit, childProcess.registers.rip - 1);
                    if(currentHitBreakpoint){
                        break;
                    }
                }

                if(currentHitBreakpoint){
                    TRACE("Found a breakpoint, fixing it.\n");

                    u8 tmp = get8(childProcess.registers.rip);
                    TRACE("Next byte code 0x%08x from address 0x%08x\n", tmp, childProcess.registers.rip);

                    tmp = get8(currentHitBreakpoint->address);
                    TRACE("Original byte code 0x%08x from address 0x%08x\n", tmp, currentHitBreakpoint->address);

                    u64 opcodes = get64(currentHitBreakpoint->address);
                    u64 correctionMask = ((opcodes >> 8) << 8) | currentHitBreakpoint->originalByteCode;
                    set64(currentHitBreakpoint->address, correctionMask);

                    tmp = get8(currentHitBreakpoint->address);
                    TRACE("New byte code 0x%08x from address 0x%08x\n", tmp, currentHitBreakpoint->address);

                    childProcess.registers.rip = currentHitBreakpoint->address;

                    ptrace(PTRACE_SETREGS, childProcess.pid, NULL, &childProcess.registers);

                    // invalidate breakpoint so no hit next time
                    currentHitBreakpoint->address = 0;
                    currentHitBreakpoint->originalByteCode = 0;
                }
            }
            break;

        case CLD_DUMPED: {
                TRACE("The child had an exception! \n");
            }
            break;

        case CLD_EXITED:{
                TRACE("The child exited! \n");
            }
            break;

        case CLD_KILLED:{
                TRACE("The child was killed! \n");
            }
            break;

        case CLD_STOPPED:{
                TRACE("The child was stopped! \n");
            }
            break;

        case CLD_CONTINUED:{
                TRACE("The child has continued! \n");
            }
            break;

        default: {
                TRACE("Unknown signal code was received si_code %d\n", signalInfo->si_code);
            }
            break;
    }
    ptrace(PTRACE_GETREGS, childProcess.pid, NULL, &childProcess.registers);
    TRACE("rip: 0x%08x current instruction: 0x%08x\n", childProcess.registers.rip, get8(childProcess.registers.rip));
    
    childProcess.available = true; // TODO(Sarmis) mutex this
    TRACE("child is available\n");
    
    fflush(stdout);
}
