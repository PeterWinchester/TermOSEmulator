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

string command;
vector<string> cmdArgs;

int startUp();
int checkPath(char*);
int mount();

int main(int argc, char const *argv[]) {
  if (!startUp()) return 0;
  if (!mount()) {
    printf("\nError! Please check your root path!\n");
    cmdArgs.clear();
    pause(cmdArgs);
    return 0;
  }
  return 0;
}

//Show the start page ang get root path.
int startUp() {
  printf("Welcome to TermOSEmulator Installer.\n");
  printf("Please type a path to mount the root directory /(The last character is '/' or '\\'):\n");

  /* In this loop, TOSEInstaller will get the root path. */
  while (true) {
    gets(systemRootPath);
    int len = strlen(systemRootPath);
    if (!len) return 0;
    if (systemRootPath[len-1]!='/' & systemRootPath[len-1]!='\\') continue;
    if (checkPath(systemRootPath)) break;
    printf("Cannot find the path, please type again or type ENTER to exit:\n");
  }
  return 1;
}

//Check if a path is correct.
int checkPath(char* path) {
  static char address[MAX_STRING_LEN];
  for (int i=0; i<strlen(path); i++) address[i] = path[i];
  strcat(address, "mount.txt");
  FILE* lpfile = fopen(address, "w+");
  if (lpfile) {
    fclose(lpfile);
    return 1;
  }
  return 0;
}

//Mount the root path.
int mount() {
  printf("mounting...");
  strcat(systemRootPath, "TermOSEmulator/");
  if (!CreateDirectoryA((LPCSTR)systemRootPath, NULL)) return 0;
  static char dir[MAX_STRING_LEN];
  strcat(dir, systemRootPath);
  strcat(dir, "bin/");
  if (!CreateDirectoryA((LPCSTR)dir, NULL)) return 0;
  printf("done!\n");
  return 1;
}
