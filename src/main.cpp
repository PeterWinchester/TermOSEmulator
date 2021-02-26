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

string command;
vector<string> cmdArgs;

int initTermOSEmulator();
void startUp();
int getSystemRootPath();
int initExplorer();

int main(int argc, char const *argv[]) {
  if (!initTermOSEmulator()) { //Failed to initailize TOSE.
    printf("Error! Cannot load system data.\n");
    printf("Please check the files in the /dat directory.\n");
    cmdArgs.clear();
    pause(cmdArgs);
    return 0;
  }
  startUp();
  
  /* This is the whole procedure that contains the user's operations. */
  while (toseRunning) {
    for (int i=0; i<strlen(systemRootPath); i++) printf("%c", systemRootPath[i]);
    printf("\n");
    cmdArgs.clear();
    pause(cmdArgs);
    exitSys(cmdArgs);
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
  printf("See the file LICENSE for more information about GPL.\n");
  printf("Visit https://github.com/PeterWinchester/TermOSEmulator for source code.\n");
  printf("The writer's email is wincsoft_pw@outlook.com. To report bugs, please\n");
  printf("visit https://github.com/PeterWinchester/Termosemulator/issues, or you\n");
  printf("can mail the writer.\n\n");
  printf("Type 'help' for help or type 'exit' to quit.\n\n");
}

//Get root path from /dat/systempath.txt.
int getSystemRootPath() {
  FILE *fin = fopen("../dat/rootpath.txt", "r");
  if (fin == NULL) return 0; //Failed.
  int len = 0;
  char cGet;
  while (fscanf(fin, "%c", &cGet) == 1) systemRootPath[len++] = cGet;
  fclose(fin);
  return 1;
}

//Initailize the explorer.
int initExplorer() {
  
}