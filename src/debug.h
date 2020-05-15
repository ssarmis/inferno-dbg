#pragma once

#include "general.h"
#include "debug_info.h"
#include "debug_aranges.h"
#include "process.h"

#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

Buffer<DWARFDebugRangeSetEntry> dwarfReadDebugData(const char* filename);
