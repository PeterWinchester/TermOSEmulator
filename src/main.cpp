/*
 * main.cpp
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

#include "TermOSEmulator.h"

int initTermOSEmulator();
void startUp();
int getSystemRootPath();

int main(int argc, char const *argv[]) {
  if (!initTermOSEmulator()) {
    printf("Error! Cannot load system data.\n");
    printf("Please check the files in the /dat directory.\n");
  }
  startUp();
  while (toseRunning) {
    pause(NULL);
    exitSys(NULL);
  }
  return 0;
}

int initTermOSEmulator() {
  toseRunning = true;
  if (!getSystemRootPath()) return 0;
  return 1;
}

void startUp() {
  
}

int getSystemRootPath() {
  return 1;
}
