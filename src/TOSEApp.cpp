/*
 * TOSEApp.cpp
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

#include "TOSEApp.h"

int numApplications;

Application apps[MAX_NUM_APPLICAITONS];

//Start an application.
int startApplication(int hApp) {
    string dir;
	for (int i = 0; i < strlen(systemRootPath); i++) {
		dir.push_back(systemRootPath[i]);
	}
	dir += "etc/";
	dir += apps[hApp].name;
	dir += ".exe";
	int res = system(dir.c_str());
	return res == 0;
}