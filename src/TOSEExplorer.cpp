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

Directory *dirRoot, *dirCrt;
vector<string> pathCrt;

TOSEFile::TOSEFile() {
  name.clear();
  type.clear();
}

Directory::Directory() {
  dirFather = NULL;
  name.clear();
  dirChild.clear();
  file.clear();
};

//Create a new directory.
int createNewDir(string argName) {
  if (argName == "") return 0;      //Invalid name, failed to create.
  try {                             //Avoid some unkown errors.
    Directory* tmp = new Directory; //This step means a new directory will be created.
    /* Initailize the basic information of the directory. */
    tmp->name = argName;
    tmp->dirFather = dirCrt;
    dirCrt->dirChild.push_back(tmp);
  } catch(...) {
    return 0; //Failed.
  }
  return 1; //Success.
}

//Create a new file.
int createNewFile(string argName, string argType) {
  if (argName == "" | argType == "") return 0; //Invalid information, failed.
  try {                                        //Avoid some unkown errors.
    TOSEFile tmp;                              //Create a new file.
    /* Initailize basic information. */
    tmp.name = argName, tmp.type = argType;
    dirCrt->file.push_back(tmp);
  } catch(...) {
    return 0; //Failed.
  }
  return 1; //Success.
}

//Change the directory.
int goToDir(string argName) {
  if (argName == "") return 0;       //Invalid parameter.
  if (argName == "..") {             //The requested directory is parent directory.
    if (dirCrt == dirRoot) return 0; //The root dirctory doesn't have parent.
    dirCrt = dirCrt->dirFather;      //Change.
    pathCrt.pop_back();              //Change the path.
    return 1;                        //Success.
  }
  for (int i = 0; i < dirCrt->dirChild.size(); i++) { //Find the requested directory.
    if (dirCrt->dirChild[i]->name == argName) {       //Got it.
      dirCrt = dirCrt->dirChild[i];                   //Change.
      pathCrt.push_back(argName);                     //Change the path.
      return 1;                                       //Success.
    }
  }
  return 0; //Failed.
}
