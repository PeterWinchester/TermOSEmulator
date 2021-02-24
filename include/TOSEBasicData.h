/*
 * TOSEBasicData.h
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

#ifndef TOSE_BASIC_DATA_H
#define TOSE_BASIC_DATA_H

#include "TermOSEmulator.h"

#define MAX_STRING_LEN 1000

extern bool toseRunning; //A sign to check if TOSE is running.
extern char systemRootPath[MAX_STRING_LEN]; //The root path of TOSE.

#endif //TOSE_BASIC_DATA_H
