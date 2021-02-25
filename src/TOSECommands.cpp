/*
 * TOSECommands.cpp
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

#include "TOSECommands.h"

CmdFunc cmdOpt[NUM_COMMANDS] = {
  pause, exitSys
};

int pause(vector<string> args) {
  printf("Press any key to continue...");
  getch();
  printf("\n");
  return 0;
}

int exitSys(vector<string> args) {
  toseRunning = false; //This means TOSE will quit!
  return 0;
}
