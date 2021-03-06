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
int install();

int main(int argc, char const *argv[]) {
  /* Load start page. */
  if (!startUp()) return 0;

  /* Mount root path. */
  if (!mount()) {
    printf("\nError! Please check your root path!\n");
    printf("If you have installed TermOSEmulator in your root path before,\n");
    printf("please remove it first.\n");
    cmdArgs.clear();
    pause(cmdArgs);
    return 0;
  }

  /* Install. */
  if (!install()) {
    cmdArgs.clear();
    pause(cmdArgs);
    return 0;
  }

  /* Finished. */
  printf("Now you have installed TermOSEmulator.\n");
  printf("You can go to /bin/ and run TermOSEmulator.exe to start TermOSEmulator.\n");
  cmdArgs.clear();
  pause(cmdArgs);
  return 0;
}

//Show the start page ang get root path.
int startUp() {
  color(7);
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
  if (access(address, 0) != -1) return 1; //Path not found.
  return 0;
}

//Mount the root path.
int mount() {
  printf("Mounting...");

  /* Create the root directory. */
  strcat(systemRootPath, "TermOSEmulator/");
  if (!CreateDirectoryA((LPCSTR)systemRootPath, NULL)) return 0;

  static char dir[MAX_STRING_LEN]; //The directory that will be created.

  /* Create the /bin directory. */
  strcat(dir, systemRootPath);
  strcat(dir, "bin/");
  if (!CreateDirectoryA((LPCSTR)dir, NULL)) return 0;

  /* Create /bin/help directory. */
  memset(dir, 0, sizeof(dir));
  strcat(dir, systemRootPath);
  strcat(dir, "bin/help/");
  if (!CreateDirectoryA((LPCSTR)dir, NULL)) return 0;

  /* Create the /home directory. */
  memset(dir, 0, sizeof(dir));
  strcat(dir, systemRootPath);
  strcat(dir, "home/");
  if (!CreateDirectoryA((LPCSTR)dir, NULL)) return 0;

  /* Create the /dat directory. */
  memset(dir, 0, sizeof(dir));
  strcat(dir, systemRootPath);
  strcat(dir, "dat/");
  if (!CreateDirectoryA((LPCSTR)dir, NULL)) return 0;

  /* Create the /etc directory. */
  memset(dir, 0, sizeof(dir));
  strcat(dir, systemRootPath);
  strcat(dir, "etc/");
  if (!CreateDirectoryA((LPCSTR)dir, NULL)) return 0;

  /* Finished. */  
  printf("done!\n");
  return 1;
}

//Install TermOSEmulator.
int install() {
  printf("Installing...");
  FILE *fin, *fout;

  /* Copy the TermOSEmulator.exe. */
  fin = fopen("TermOSEmulator.exe", "rb");
  if (fin == NULL) {
    printf("\nError: cannot find TermOSEmulator.exe.\n");
    return 0;
  }
  static char dir[MAX_STRING_LEN];
  strcat(dir, systemRootPath);
  strcat(dir, "bin/TermOSEmulator.exe");
  fout = fopen(dir, "wb");
  char cGet;
  while (fscanf(fin, "%c", &cGet) == 1) fprintf(fout, "%c", cGet);
  fclose(fin);
  fclose(fout);

  /* Record the root path. */
  memset(dir, 0, sizeof(dir));
  strcat(dir, systemRootPath);
  strcat(dir, "dat/rootpath.txt");
  fout = fopen(dir, "w");
  for (int i=0; i<strlen(systemRootPath); i++) {
    fprintf(fout, "%c", systemRootPath[i]);
  }
  fprintf(fout, "\r");
  fclose(fout);

  /* Initailize the explorer. */
  memset(dir, 0, sizeof(dir));
  strcat(dir, systemRootPath);
  strcat(dir, "dat/explorerdat.txt");
  fout = fopen(dir, "w");
  fprintf(fout, "md bin\r");
  fprintf(fout, "cd bin\r");
  fprintf(fout, "md help\r");
  fprintf(fout, "mf TermOSEmulator exe\r");
  fprintf(fout, "cd ..\r");
  fprintf(fout, "md dat\r");
  fprintf(fout, "cd dat\r");
  fprintf(fout, "mf rootpath txt\r");
  fprintf(fout, "mf explorerdat txt\r");
  fprintf(fout, "cd ..\r");
  fprintf(fout, "md etc\r");
  fprintf(fout, "md home\r");
  fclose(fout);

  printf("done!\n"); //Finished.
  return 1;
}
