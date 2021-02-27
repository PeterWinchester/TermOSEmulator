/*
 * TOSEExplorer.cpp
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

#include "TOSEExplorer.h"

Directory* dirRoot;

TOSEFile::TOSEFile() {
  name.clear();
  type.clear();
}

Directory::Directory() {
  dirFather = NULL;
};

Directory::~Directory() {
  delete dirFather;
}

int createNewDir(Directory* argDir, string argName) {
  if (argDir==NULL | argName=="") return 0;
  try {
    Directory* tmp = new Directory;
    tmp->name = argName;
    tmp->dirFather = argDir;
    argDir->dirChild.push_back(tmp);
    delete tmp;
  } catch(...) {
    return 0;
  }
  return 1;
}

int createNewFile(Directory* argDir, string argName, string argType) {
  if (argName=="" | argType=="" | argDir==NULL) return 0;
  try {
    TOSEFile tmp;
    tmp.name = argName, tmp.type = argType;
    argDir->file.push_back(tmp);
  } catch(...) {
    return 0;
  }
  return 1;
}

int goToDir(Directory* argDir, string argName) {
  if (argDir==NULL | argName=="") return 0;
  if (argName == "..") {
    argDir = argDir->dirFather;
    return 1;
  }
  for (int i=0; i<argDir->dirChild.size(); i++) {
    if (argDir->dirChild[i]->name == argName) {
      argDir = argDir->dirChild[i];
      return 1;
    }
  }
  return 0;
}