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
  pause, exitSys, ls, cd, mkdir
};

string cmdName[NUM_COMMANDS] = {
  "pause", "exit", "ls", "cd", "mkdir"
};

int pause(vector<string> args) {
  if (args.size()) {
    printf("The command 'pause' doesn't need any parameter.\n");
    return 0;
  }
  printf("Press any key to continue...");
  getch();
  printf("\n");
  return 1;
}

int exitSys(vector<string> args) {
  if (args.size()) {
    printf("The command 'exit' doesn't need any parameter.\n");
    return 0;
  }
  toseRunning = false; //This means TOSE will quit!
  return 1;
}

int ls(vector<string> args) {
  if (args.size()) {
    printf("The command 'ls' doesn't need any parameter.\n");
    return 0;
  }
  if (dirCrt != dirRoot) {
    color(9);
    printf(".. ");
    color(7);
  }
  color(9);
  for (int i = 0; i < dirCrt->dirChild.size(); i++) {
    cout << dirCrt->dirChild[i]->name << " ";
  }
  color(7);
  for (int i = 0; i < dirCrt->file.size(); i++) {
    if (dirCrt->file[i].type == "exe") {
      color(10);
      cout << dirCrt->file[i].name << "." << dirCrt->file[i].type << " ";
      color(7);
    } else {
      cout << dirCrt->file[i].name << "." << dirCrt->file[i].type << " ";
    }
  }
  cout << endl;
  return 1;
}

int cd(vector<string> args) {
  if (args.size() == 0) {
    printf("The command 'cd' needs an parameter.\n");
    printf("Type 'help cd' for help.\n");
    return 0;
  }
  if (args.size() > 1) {
    printf("The parameters given by you are too many.\n");
    printf("Type 'help cd' for help.\n");
    return 0;
  }
  if (!goToDir(args[0])) {
    printf("Directory not found.\n");
    return 0;
  }
  return 1;
}

int mkdir(vector<string> args) {
  if (args.size() == 0) {
    printf("The command 'mkdir' needs an parameter.\n");
    printf("Type 'help mkdir' for help.\n");
    return 0;
  }
  if (args.size() > 1) {
    printf("The parameters given by you are too many.\n");
    printf("Type 'help mkdir' for help.\n");
    return 0;
  }
  if (!createNewDir(args[0])) {
    return 0;
  }
  return 1;
}
