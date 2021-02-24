/*
 * TOSECommands.h
 * 
 * This file is a part of TermOSEmulator.
 * 
 * Written by Peter Winchester <wincsoft_pw@outlook.com>
 * Copyright (C) 2021 Peter Winchester.
 * 
 * TermOSEmulator is free software, follows the GNU General
 * Public License.
 * 
 * NOTE: TermOSEmulator requires Windows API, so it can only
 * run on the Windows.
 * 
 */

#ifndef TOSE_COMMANDS_H
#define TOSE_COMMANDS_H

#include "TermOSEmulator.h"

#define NUM_COMMANDS 2

typedef int (*CmdFunc)(const char**);

extern CmdFunc cmdOpt[NUM_COMMANDS];

int pause(const char**);
int exitSys(const char**);

#endif //TOSE_COMMANDS_H