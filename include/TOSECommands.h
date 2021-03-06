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

#define NUM_COMMANDS 5

typedef int (*CmdFunc)(vector<string>);

/* These pointers point the functions to execute TOSE commands. */
extern CmdFunc cmdOpt[NUM_COMMANDS];
extern string cmdName[NUM_COMMANDS];

int pause(vector<string>);   //Execute the command 'pause'.
int exitSys(vector<string>); //Execute the command 'exit'.
int ls(vector<string>);      //Execute the command 'ls'.
int cd(vector<string>);      //Execute the command 'cd'.
int mkdir(vector<string>);   //Execute the command 'mkdir'.

#endif //TOSE_COMMANDS_H
