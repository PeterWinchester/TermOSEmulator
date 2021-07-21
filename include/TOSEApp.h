/*
 * TOSEApp.h
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

#ifndef TOSE_APP_H
#define TOSE_APP_H

#include "TermOSEmulator.h"

#define MAX_NUM_APPLICAITONS 100

extern int numApplications;

class Application
{
public:
    string name;
};

extern Application apps[MAX_NUM_APPLICAITONS];

int startApplication(int);
int installApp();
int removeApp();
int listApps();
int autoRemove();
void updateAppData();

#endif //TOSE_APP_H
