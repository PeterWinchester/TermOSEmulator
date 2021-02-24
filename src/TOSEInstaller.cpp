/*
 * TOSEInstaller.cpp
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

void startUp();
int checkPath(char*);
void mount();

int main(int argc, char const *argv[]) {
  startUp();
  return 0;
}
//Show the start page.
void startUp() {
  printf("Welcome to TermOSEmulator Installer.\n");
  printf("Please type a path to mount the root directory /(The last character is '/' or '\\'):\n");
  /* In this loop, TOSEInstaller will get the root path. */
  while (true) {
    gets(systemRootPath);
    if (checkPath(systemRootPath)) break;
    printf("Cannot find the path, please type again or type ENTER to exit:\n");
  }
  printf("mounting...");
  mount();
}
//Check if a path is correct.
int checkPath(char* path) {
  char *address = path;
  strcat(address, "mount.txt");
  FILE* lpfile = fopen(address, "w+");
  if (lpfile) {
    fclose(lpfile);
    return 1;
  }
  return 0;
}
//Mount the root path.
void mount() {
  static char cmd[MAX_STRING_LEN]; //The command that will be executed in cmd.
  
}
