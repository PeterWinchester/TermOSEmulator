/*
 * TOSEBasicData.cpp
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

#include "TOSEBasicData.h"

bool toseRunning;
char systemRootPath[MAX_STRING_LEN];

void color(int arg) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), arg);
}
