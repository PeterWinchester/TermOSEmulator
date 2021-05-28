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
char dir[MAX_STRING_LEN];
char installPath[MAX_STRING_LEN];
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

int installApp() {
    
    /* Type the path. */
    printf("Please type the path of the executable file:\n");
    memset(dir, 0, sizeof(dir));
    gets(dir);
    
    /* Check the path. */
    FILE* fin = fopen(dir, "rb");
    if (fin == NULL) { //Cannot find the file.
        printf("The executable file doesn't exist.\n");
        return 0;
    }
    int pos = strlen(dir) - 1;
    string exeFileName;
    while (pos >= 0 && dir[pos] != '/') pos--;
    for (int i = pos + 1; i < strlen(dir); i++) {
        exeFileName.push_back(dir[i]);
    }
    memset(installPath, 0, sizeof(installPath));
    strcat(installPath, systemRootPath);
    strcat(installPath, "etc/");
    strcat(installPath, exeFileName.c_str());
    FILE* fout = fopen(installPath, "wb");
    if (fout == NULL) {
        printf("Cannot install the app, please check the directory /etc.\n");
        fclose(fin);
        return 0;
    }
    Directory* dirPos = dirCrt;
    while (dirPos->name != "root") dirPos = dirPos->dirFather;
    for (int i = 0; i < dirPos->dirChild.size(); i++) {
        if (dirPos->dirChild[i]->name == "etc") {
            dirPos = dirPos->dirChild[i];
            break;
        }
    }
    string exeName, exeType = "exe";
    for (int i = exeFileName.length() - 1; i >= 0; i--) {
        if (exeFileName[i] == '.') {
            for (int j = 0; j < i; j++) {
                exeName.push_back(exeFileName[j]);
            }
        }
    }
    /*
    for (int i = 0; i < dirPos->file.size(); i++) {
        if (dirPos->file[i].name == exeName && dirPos->file[i].type == exeType) {
            if (fin) fclose(fin);
            if (fout) fclose(fout);
            printf("The name of two apps can't be the same.\n");
            return 0;
        }
    }
    */
    for (int i = 0; i < numApplications; i++) {
        if (apps[i].name == exeName) {
            if (fin) fclose(fin);
            if (fout) fclose(fout);
            printf("The name of two apps can't be the same.\n");
            return 0;
        }
    }

    /* Install app. */
    char cGet;
    while (fscanf(fin, "%c", &cGet) == 1) {
        fprintf(fout, "%c", cGet);
    }
    fclose(fin);
    fclose(fout);
    TOSEFile tmp;
    tmp.name = exeName, tmp.type = exeType;
    dirPos->file.push_back(tmp);
    apps[numApplications++].name = exeName;
    updateExplorer();
    updateAppData();
    printf("Installed.\n");
    return 1;
}

int removeApp() {
    return 1;
}

void updateAppData() {
    ofstream fout;
    fout.open("../dat/sysappdat.txt", ios::out);
    fout << numApplications << endl;
    for (int i = 0; i < numApplications; i++) {
        fout << apps[i].name << endl;
    }
    fout.close();
}
