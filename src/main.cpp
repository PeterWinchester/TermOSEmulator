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
int initApplications();
int TranslateCmd();
int ProcessCmd();

int main(int argc, char const* argv[]) {
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
        gets(cmdTyped);       //Type command.
        if (TranslateCmd()) { //Translate command.
            ProcessCmd();     //Process command.
        }
    }
    return 0;
}

//Initailize TOSE.
int initTermOSEmulator() {
    toseRunning = true;                 //This means TOSE begins running!
    color(7);
    if (!getSystemRootPath()) return 0; //Failed to get root path.
    if (!initExplorer()) return 0;      //Failed to initailize explorer.
    if (!initApplications()) return 0;  //Failed to initailize apps.
    return 1;
}

//Load the start page.
void startUp() {
    printf("Welcome to TermOSEmulator!\n\n");
    printf("Copyright (C) 2021 Peter Winchester.\n\n");
    printf("TermOSEmulator is free software, follows the GNU General Public License.\n");
    printf("See the file LICENSE for more information about GPL.\n");
    printf("Visit https://github.com/PeterWinchester/TermOSEmulator for source code.\n");
    printf("The writer's email is wincsoft_pw@outlook.com. To report bugs, please\n");
    printf("visit https://github.com/PeterWinchester/Termosemulator/issues, or you\n");
    printf("can mail the writer.\n\n");
    printf("Type 'help' for help or type 'exit' to quit.\n\n");
}

//Get root path from /dat/systempath.txt.
int getSystemRootPath() {
    FILE* fin = fopen("../dat/rootpath.txt", "r");
    if (fin == NULL) return 0; //Failed.
    int len = 0;
    char cGet;
    while (fscanf(fin, "%c", &cGet) == 1 && cGet != '\r') systemRootPath[len++] = cGet;
    fclose(fin);
    return 1;
}

//Initailize applications.
int initApplications() {
    /* Check the file. */
    FILE* test = fopen("../dat/sysappdat.txt", "r");
    if (test == NULL) { //Cannot find the file.
        return 0;       //Failed.
    }

    /* Get data. */
    ifstream fin("../dat/sysappdat.txt");
    fin >> numApplications;
    for (int i = 0; i < numApplications; i++) {
        fin >> apps[i].name;
    }
    fin.close();
    return 1; //Succeeded.
}

//Translate the typed command.
int TranslateCmd() {
    if (strlen(cmdTyped) == 0) { //Didn't type any thing.
        return 0;                //Needn't to translate.
    }

    /* Preprocess. */
    cmdArgs.clear();
    for (int i = 0; i < strlen(cmdTyped); i++) {
        if (cmdTyped[i] != ' ' && (i == 0 || cmdTyped[i - 1] == ' ')) {
            /* Meet a new word. */
            string tmp;
            tmp.push_back(cmdTyped[i]);
            cmdArgs.push_back(tmp);                             //Add it.
        } else if (cmdTyped[i] != ' ') {                        //Not a new word.
            cmdArgs[cmdArgs.size() - 1].push_back(cmdTyped[i]); //Add a character.
        }
    }
    if (cmdArgs.size() == 0) return 0; //Didn't type any command.
    command = cmdArgs[0]; //The commad is the first word.

    /* Process the arguments. */
    for (int i = 0; i < cmdArgs.size() - 1; i++) {
        cmdArgs[i] = cmdArgs[i + 1];
    }
    cmdArgs.pop_back();
    return 1; //Translated.
}

//Process the command.
int ProcessCmd() {
    /* Search the command. */
    for (int i = 0; i < NUM_COMMANDS; i++) {
        if (cmdName[i] == command) { //Found.
            return cmdOpt[i](cmdArgs); //Execute it.
        }
    }

    /* Look up the apps. */
    for (int i = 0; i < numApplications; i++) {
        if (command == apps[i].name) {  //Found.
            return startApplication(i); //Start the app.
        }
    }
    printf("'");
    cout << command;
    printf("' is not a command or an executable file.\n");
    return 0;
}
