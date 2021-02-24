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
  if (!initTermOSEmulator()) { //Failed to initailize TOSE.
    printf("Error! Cannot load system data.\n");
    printf("Please check the files in the /dat directory.\n");
    pause(NULL);
    return 0;
  }
  startUp();
  /* This is the whole procedure that contains the user's operations. */
  while (toseRunning) {
    pause(NULL);
    exitSys(NULL);
  }
  return 0;
}
//Initailize TOSE.
int initTermOSEmulator() {
  toseRunning = true; //This means TOSE begins running!
  if (!getSystemRootPath()) return 0; //Failed to get root path.
  return 1;
}
//Load the start page.
void startUp() {
  printf("Welcome to TermOSEmulator!\n\n");
  printf("Copyright (C) 2021 Peter Winchester.\n\n");
  printf("TermOSEmulator is free software, follow the GNU General Public License.\n");
  printf("See https://www.gnu.org/ for more information about the GPL.\n");
  printf("Visit https://github.com/PeterWinchester/TermOSEmulator for source code.\n");
  printf("The writer's email is wincsoft_pw@outlook.com. To report bugs, please\n");
  printf("visit https://github.com/PeterWinchester/Termosemulator/issues, or you\n");
  printf("can mail the writer.\n");
}

int getSystemRootPath() {
  return 1;
}
