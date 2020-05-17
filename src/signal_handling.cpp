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

#define DTRACE

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

static BreakpointType lastBreakpointType = BREAKPOINT_NONE;

void signalChildHandler(int signalNumber, siginfo_t* signalInfo, void/* ucontext_t */* context){
    DTRACE("Received signal %d %llx\n", signalNumber, signalInfo->si_errno);

    switch(signalInfo->si_code){
        case CLD_TRAPPED:{
                DTRACE("The child is trapped! %d\n", signalInfo->si_status);
                int signalStatus = signalInfo->si_status;
                if(WIFSIGNALED(signalStatus)){
                    switch (WTERMSIG(signalStatus)){
                        case SIGSEGV:{
                                DTRACE("Program ended in segmentation fault\n");
                                childProcess.alive = false;
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
                    lastBreakpointType = currentHitBreakpoint->type;

                    DTRACE("Found a breakpoint, fixing it.\n");

                    u8 tmp = get8(childProcess.registers.rip);

                    tmp = get8(currentHitBreakpoint->address);

                    u64 opcodes = get64(currentHitBreakpoint->address);
                    u64 correctionMask = ((opcodes >> 8) << 8) | currentHitBreakpoint->originalMachineCode;
                    set64(currentHitBreakpoint->address, correctionMask);

                    tmp = get8(currentHitBreakpoint->address);

                    childProcess.registers.rip = currentHitBreakpoint->address;

                    ptrace(PTRACE_SETREGS, childProcess.pid, NULL, &childProcess.registers);

                    // invalidate breakpoint so no hit next time
                    currentHitBreakpoint->type = BREAKPOINT_NONE;
                    currentHitBreakpoint->address = 0;
                    currentHitBreakpoint->originalMachineCode = 0;
                }
            }
            break;

        case CLD_DUMPED: {
                TRACE("The child had an exception! \n");
            }
            break;

        case CLD_EXITED:{
                TRACE("The child exited! \n");
                childProcess.alive = false;
            }
            break;

        case CLD_KILLED:{
                TRACE("The child was killed! \n");
                childProcess.alive = false;
            }
            break;

        case CLD_STOPPED:{
                TRACE("The child was stopped! \n");
                childProcess.alive = false;
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
    
    if(childProcess.alive){
        ptrace(PTRACE_GETREGS, childProcess.pid, NULL, &childProcess.registers);
        DTRACE("rip: 0x%llx current instruction: 0x%llx\n", childProcess.registers.rip, get8(childProcess.registers.rip));
        
        childProcess.available = true; // TODO(Sarmis) mutex this
        DTRACE("child is available\n");

        if(lastBreakpointType == BREAKPOINT_INTERNAL){
            if(childProcess.steppingIsEnabled){
                childProcess.steppingIsEnabled = false;
            } else {
                debugContinue();
            }
        }
    }

    fflush(stdout);
}












