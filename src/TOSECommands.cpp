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

string cmdName[NUM_COMMANDS] = {
  "pause", "exit"
};

int pause(vector<string> args) {
  if (args.size()) {
    printf("The command 'pause' doesn't need any argument.\n");
    return 0;
  }
  printf("Press any key to continue...");
  getch();
  printf("\n");
  return 1;
}

int exitSys(vector<string> args) {
  if (args.size()) {
    printf("The command 'exit' doesn't need any argument.\n");
    return 0;
  }
  toseRunning = false; //This means TOSE will quit!
  return 1;
}
