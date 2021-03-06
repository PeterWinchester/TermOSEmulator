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

char cmdTyped[MAX_STRING_LEN];
string command;
vector<string> cmdArgs;

int initTermOSEmulator();
void startUp();
int getSystemRootPath();
int initExplorer();
void TranslateCmd();
int ProcessCmd();

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
    /* Print the path. */
    for (int i = 0; i < pathCrt.size(); i++) {
      cout << pathCrt[i];
      if (i < pathCrt.size() - 1) printf("/");
    }
    printf(" $ ");
    gets(cmdTyped); //Type command.
    TranslateCmd(); //Translate command.
    ProcessCmd();   //Process command.
  }
  return 0;
}

//Initailize TOSE.
int initTermOSEmulator() {
  toseRunning = true;                 //This means TOSE begins running!
  color(7);
  if (!getSystemRootPath()) return 0; //Failed to get root path.
  if (!initExplorer()) return 0;      //Failed to initailize explorer.
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
  while (fscanf(fin, "%c", &cGet) == 1 && cGet != '\r') systemRootPath[len++] = cGet;
  fclose(fin);
  return 1;
}

//Initailize the explorer.
int initExplorer() {
  /* Create the root directory. */
  dirRoot = new Directory;
  dirRoot->name = "root";
  dirCrt = dirRoot;
  pathCrt.push_back("root");

  /* Check the file. */
  string opt;
  FILE *test = fopen("../dat/explorerdat.txt", "r");
  if (test == NULL) {
    return 0;
  }
  fclose(test);

  /* Get dat. */
  ifstream fin("../dat/explorerdat.txt");
  while (fin >> opt) {
    if (opt == "md") { //Create a child directory.
      string name;
      fin >> name;
      if (!createNewDir(name)) {
        fin.close();
        return 0;
      }
    } else if (opt == "mf") { //Create a new file.
      string name, type;
      fin >> name >> type;
      if (!createNewFile(name, type)) {
        fin.close();
        return 0;
      }
    } else if (opt == "cd") { //Move to a directory.
      string name;
      fin >> name;
      if (!goToDir(name)) {
        fin.close();
        return 0;
      }
    }
  }
  fin.close();
  return 1;
}

//Translate the typed command.
void TranslateCmd() {
  /* Preprocess. */
  cmdArgs.clear();
  for (int i = 0; i < strlen(cmdTyped); i++) {
    if (cmdTyped[i] != ' ' && (i == 0 || cmdTyped[i - 1] == ' ')) {
      /* Meet a new word. */
      string tmp;
      tmp.push_back(cmdTyped[i]);
      cmdArgs.push_back(tmp);                             //Add it.
    } else if (cmdTyped[i] != ' ') {                      //Not a new word.
      cmdArgs[cmdArgs.size() - 1].push_back(cmdTyped[i]); //Add a char.
    }
  }
  command = cmdArgs[0]; //The commad is the first word.
  
  /* Process the arguments. */
  for (int i = 0; i < cmdArgs.size() - 1; i++) {
    cmdArgs[i] = cmdArgs[i + 1];
  }
  cmdArgs.pop_back();
}

//Process the command.
int ProcessCmd() {
  /* Search the command. */
  for (int i = 0; i < NUM_COMMANDS; i++) {
    if (command == cmdName[i]) { //Found.
      return cmdOpt[i](cmdArgs); //Execute it.
    }
  }
  printf("Command not found.\n"); //Not found.
  return 0;
}
