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

class File {
public:
  string name, type;
		
  File();
};

File::File() {
  name.clear();
  type.clear();
}

class Directory {
public:
  string name;
  Directory *dirFather;
  int numChild;
  vector<Directory*> dirChild;
  int numFile;
  vector<File> file;

  Directory();
};

Directory::Directory() {
  dirFather = NULL;
  numChild = 0;
  numFile = 0;
};

extern Directory* dirRoot;

#endif //TOSE_EXPLORER_H
