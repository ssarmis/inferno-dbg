#pragma once

#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <stdlib.h>
#include <errno.h>

#include "general.h"
#include "debug_info.h"

void attach(pid_t pid);
void set64(u64 address, u64 data);
u64 get64(u64 address);
u8 get8(u64 address);
void updateRegisters();
void debugWaitForProcessToBeAvailable();
void launchChildProcess(const char* filename, char* arguments[]);
void debugSetBreakpoint(DWARFDebugCompilationUnit* compilationUnit, u64 address);
void debugStepInstruction();
void debugStepLine( /*, u64 line */);
void debugContinue();