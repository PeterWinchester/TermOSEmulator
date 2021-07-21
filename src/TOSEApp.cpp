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
int startApplication(int hApp)
{
    string dir; //The path of app.
    for (int i = 0; i < strlen(systemRootPath); i++)
    {
        dir.push_back(systemRootPath[i]);
    }
    dir += "etc/";
    dir += apps[hApp].name;
    dir += ".exe";
    /* Check if the executable file exists. */
    FILE *ftest = fopen(dir.c_str(), "rb");
    if (ftest == NULL)
    {
        printf("Can't find the executable file on Windows.\n");
        return 0;
    }
    fclose(ftest);
    int res = system(dir.c_str()); //Execute it.
    return res == 0;
}

int installApp()
{

    /* Type the path. */
    printf("Please type the path of the executable file:\n");
    memset(dir, 0, sizeof(dir));
    gets(dir); //Enter the path and store it in the string dir.

    /* Check the path. */
    FILE *fin = fopen(dir, "rb");
    if (fin == NULL) //Cannot find the file.
    {
        printf("The executable file doesn't exist.\n");
        return 0;
    }

    string exeFileName, exeName, exeType;

    /* Get the name of executable file. */
    int pos = strlen(dir) - 1;
    while (pos >= 0 && dir[pos] != '/')
        pos--; //Find the last '/' character in the string dir.
    /* The part of the string dir after the last '/' is the file name. */
    for (int i = pos + 1; i < strlen(dir); i++)
    {
        exeFileName.push_back(dir[i]);
    }

    /* Get the installation directory. */
    memset(installPath, 0, sizeof(installPath));
    strcat(installPath, systemRootPath);
    strcat(installPath, "etc/");
    strcat(installPath, exeFileName.c_str());
    FILE *fout = fopen(installPath, "wb"); //Check the installation directory.
    if (fout == NULL)
    {
        printf("Cannot install the app, please check the directory /etc.\n");
        fclose(fin);
        return 0;
    }

    /* Get file type. */
    for (int i = exeFileName.length() - 1; i >= 0; i--)
    {
        /* The part of string exeFilename after the last '.' is the file type. */
        if (exeFileName[i] == '.')
        {
            for (int j = i + 1; j < exeFileName.length(); j++)
            {
                exeType.push_back(exeFileName[j]);
            }
            break;
        }
    }
    if (exeType != "exe")
    { //The file type is wrong.
        printf("The type of executable file must be exe.\n");
        return 0;
    }

    /* Locate to the directory /etc. */
    Directory *dirPos = dirCrt;
    while (dirPos->name != "root")
        dirPos = dirPos->dirFather; //Locate to the directory /.
    for (int i = 0; i < dirPos->dirChild.size(); i++) //Locate to /etc.
    {
        if (dirPos->dirChild[i]->name == "etc")
        {
            dirPos = dirPos->dirChild[i];
            break;
        }
    }

    /* Get file name. */
    for (int i = exeFileName.length() - 1; i >= 0; i--)
    {
        //The part of string exeFileName before the last '.' is the file name.
        if (exeFileName[i] == '.')
        {
            for (int j = 0; j < i; j++)
            {
                exeName.push_back(exeFileName[j]);
            }
        }
    }

    /* Check if the app has been installed. */
    for (int i = 0; i < numApplications; i++)
    {
        if (apps[i].name == exeName) //The app has been installed.
        {
            if (fin)
                fclose(fin);
            if (fout)
                fclose(fout);
            printf("The app has been installed.\n");
            return 0;
        }
    }

    /* Install app. */
    char cGet;
    while (fscanf(fin, "%c", &cGet) == 1)
    {
        fprintf(fout, "%c", cGet); //Copy the executable file.
    }
    fclose(fin);
    fclose(fout);
    TOSEFile tmp;
    tmp.name = exeName, tmp.type = exeType;
    dirPos->file.push_back(tmp); //Add the executable file to explorer.
    apps[numApplications++].name = exeName;
    updateExplorer(); //Update the data.
    updateAppData();

    printf("Installed.\n");
    return 1;
}

int removeApp()
{
    printf("Please type the name of the app which you want to remove:\n");
    string nameReq;
    cin >> nameReq;

    /* Search the typed app. */
    bool find = false;
    for (int i = 0; i < numApplications; i++)
    {
        if (apps[i].name == nameReq)
        { //Found.
            find = true;
            break;
        }
    }
    if (!find) //Cannot find the app.
    {
        printf("Cannot find the typed app.\n");
        return 0;
    }

    /* Remove the executable file on TermOSemulator. */
    string typeReq = "exe";
    Directory *dirPos = dirRoot, *dirTmp = dirCrt;
    for (int i = 0; i < dirPos->dirChild.size(); i++)
    {
        if (dirPos->dirChild[i]->name == "etc")
        {
            dirPos = dirPos->dirChild[i];
        }
    }
    dirCrt = dirPos;
    removeFile(nameReq, typeReq);
    dirCrt = dirTmp;

    /* Remove the executable file on Windows. */
    string dir;
    for (int i = 0; i < strlen(systemRootPath); i++)
    {
        dir.push_back(systemRootPath[i]);
    }
    dir += "etc/";
    dir += nameReq;
    dir += ".exe";
    FILE *ftest = fopen(dir.c_str(), "rb");
    if (ftest != NULL)
    {
        fclose(ftest);
        string cmd = "del \"";
        cmd += dir;
        cmd += "\"";
        for (int i = 0; i < cmd.length(); i++)
        {
            if (cmd[i] == '/')
            {
                cmd[i] = '\\';
            }
        }
        system(cmd.c_str()); //Remove it.
    }

    /* Update the data. */
    for (int i = 0; i < numApplications; i++)
    {
        if (apps[i].name == nameReq)
        {
            for (int j = i; j < numApplications - 1; j++)
            {
                apps[j] = apps[j + 1];
            }
            break;
        }
    }
    numApplications--;
    updateAppData();

    printf("Removed.\n");
    return 1;
}

int autoRemove()
{
    /* TODO: Find apps that no longer needed and remove them. */
	char path[MAX_STRING_LEN];
	for (int i = 0; i < numApplications; i++)
	{
		sprintf(path, "../etc/%s.exe", apps[i].name.c_str());
		FILE *fin = fopen(path, "rb");
		if (fin == NULL)
		{
			for (int j = i; j < numApplications - 1; j++)
				apps[j] = apps[j + 1];
			numApplications--;
		}
		else fclose(fin);
	}
	updateAppData();
	return 1;
}

void updateAppData()
{
    ofstream fout;
    fout.open("../dat/sysappdat.txt", ios::out);
    fout << numApplications << endl;
    for (int i = 0; i < numApplications; i++)
    {
        fout << apps[i].name << endl;
    }
    fout.close();
}

int listApps()
{
    if (numApplications == 0)
	{
		printf("No installed application.\n");
		return 1;
	}
	printf("%d applications installed:\n", numApplications);
	for (int i = 0; i < numApplications; i++)
	{
		cout << apps[i].name << ' ';
	}
	cout << endl;
	return 1;
}
