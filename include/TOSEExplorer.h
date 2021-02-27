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

class TOSEFile {
public:
  string name, type;
		
  TOSEFile();
};

class Directory {
public:
  string name;
  Directory *dirFather;
  vector<Directory*> dirChild;
  vector<TOSEFile> file;

  Directory();
  ~Directory();
};

extern Directory* dirRoot;

int createNewDir(Directory*, string);
int createNewFile(Directory*, string, string);
int goToDir(Directory*, string);

#endif //TOSE_EXPLORER_H
