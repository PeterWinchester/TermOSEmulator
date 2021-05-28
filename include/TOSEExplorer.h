/*
 * TOSEExplorer.h
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

#ifndef TOSE_EXPLORER_H
#define TOSE_EXPLORER_H

#include "TermOSEmulator.h"

class TOSEFile { //The class of files.
public:
    string name, type;

    TOSEFile();
};

class Directory { //The class of directories.
public:
    string name;                 //The name of a directory.
    Directory* dirFather;        //The father of a directory.
    vector<Directory*> dirChild; //Children of a directory.
    vector<TOSEFile> file;       //Files of a directory.

    Directory();
    ~Directory();
};

extern Directory* dirRoot;     //The root directory.
extern Directory* dirCrt;      //The current directory.
extern vector<string> pathCrt; //The current path.

int createNewDir(string);
int createNewFile(string, string);
int goToDir(string);
int delDir(string);
int initExplorer();
void updateExplorer();
void writeExplorerData(Directory*);

#endif //TOSE_EXPLORER_H
