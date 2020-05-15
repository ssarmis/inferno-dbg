#pragma once

#include <sys/signal.h>
#include "general.h"

extern Process childProcess;

void signalChildHandler(int signalNumber, siginfo_t* signalInfo, void/* ucontext_t */* context);