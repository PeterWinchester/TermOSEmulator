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
ofstream fout;

TOSEFile::TOSEFile()
{
    name.clear();
    type.clear();
}

Directory::Directory()
{
    dirFather = NULL;
    name.clear();
    dirChild.clear();
    file.clear();
};

//Create a new directory.
int createNewDir(string argName)
{
    if (argName == "")
        return 0; //Invalid name, failed to create.

    /* Avoid having two folders with the same name. */
    for (int i = 0; i < dirCrt->dirChild.size(); i++)
    {
        if (dirCrt->dirChild[i]->name == argName)
        {
            printf("Cannot create the directory, because there is already a directory with the save name.\n");
            return 0;
        }
    }

    /* Avoid some unkown errors. */
    try
    {
        Directory *tmp = new Directory; //This step means a new directory will be created.
        /* Initailize the basic information of the directory. */
        tmp->name = argName;
        tmp->dirFather = dirCrt;
        dirCrt->dirChild.push_back(tmp);

        /* Create directory in Windows. */
        char dir[MAX_STRING_LEN];
        memset(dir, 0, sizeof(dir));
        strcat(dir, systemRootPath);
        for (int i = 1; i < pathCrt.size(); i++)
        {
            for (int j = 0; j < pathCrt[i].length(); j++)
            {
                dir[strlen(dir)] = pathCrt[i][j];
            }
            dir[strlen(dir)] = '/';
        }
        for (int i = 0; i < argName.length(); i++)
        {
            dir[strlen(dir)] = argName[i];
        }
        if (CreateDirectoryA((LPCSTR)dir, NULL))
        {
            updateExplorer();
        }
    }
    catch (...)
    {
        printf("Failed! Unknown error.\n");
        return 0; //Failed.
    }
    return 1; //Success.
}

//Create a new file.
int createNewFile(string argName, string argType)
{
    if (argName == "" | argType == "")
        return 0; //Invalid information, failed.
    try //Avoid some unkown errors.
    {
        TOSEFile tmp; //Create a new file.
        /* Initailize basic information. */
        tmp.name = argName, tmp.type = argType;
        dirCrt->file.push_back(tmp);
    }
    catch (...)
    {
        return 0; //Failed.
    }
    return 1; //Success.
}

//Remove a file.
int removeFile(string argName, string argType)
{
    if (argName == "" | argType == "")
        return 0; //Invalid arguments.
    /* Search the file. */
    for (int i = 0; i < dirCrt->file.size(); i++)
    {
        if (dirCrt->file[i].name == argName & dirCrt->file[i].type == argType) //Found.
        {
            /* Remove it. */
            for (int j = i; j < dirCrt->file.size() - 1; j++)
            {
                dirCrt->file[j] = dirCrt->file[j + 1];
            }
            dirCrt->file.pop_back();
            updateExplorer();
            return 1;
        }
    }
    return 0; //Cannot find the file.
}

//Change the directory.
int goToDir(string argName)
{
    if (argName == "")
        return 0; //Invalid parameter.
    if (argName == "..") //The requested directory is parent directory.
    {
        if (dirCrt == dirRoot)
            return 0;               //The root dirctory doesn't have parent.
        dirCrt = dirCrt->dirFather; //Change.
        pathCrt.pop_back();         //Change the path.
        return 1;                   //Success.
    }
    for (int i = 0; i < dirCrt->dirChild.size(); i++) //Find the requested directory.
    {
        if (dirCrt->dirChild[i]->name == argName)
        {                                 //Got it.
            dirCrt = dirCrt->dirChild[i]; //Change.
            pathCrt.push_back(argName);   //Change the path.
            return 1;                     //Success.
        }
    }
    return 0; //Failed.
}

//Delete a directory.
int delDir(string dirPath)
{
    /* Do it by executing a command. */
    char cmd[MAX_STRING_LEN];
    memset(cmd, 0, sizeof(cmd));
    sprintf(cmd, "rmdir /s /q \"%s\"", dirPath.c_str());
    int res = system(cmd);
    if (res == 0)
        return 1; //Success.
    return 0;     //Failed.
}

//Update the explorer.
void updateExplorer()
{
    fout.open("../dat/explorerdat.txt", ios::out);
    writeExplorerData(dirRoot);
    fout.close();
}

//Write the data of explorer.
void writeExplorerData(Directory *argDir)
{
    /* Record the data of files. */
    for (int i = 0; i < argDir->file.size(); i++)
    {
        fout << "mf " << argDir->file[i].name << " " << argDir->file[i].type << endl;
    }
    /* Record the data of direcotries. */
    for (int i = 0; i < argDir->dirChild.size(); i++)
    {
        fout << "md " << argDir->dirChild[i]->name << endl;
        fout << "cd " << argDir->dirChild[i]->name << endl;
        writeExplorerData(argDir->dirChild[i]);
        fout << "cd .." << endl;
    }
}

//Initailize the explorer.
int initExplorer()
{
    /* Create the root directory. */
    dirRoot = new Directory;
    dirRoot->name = "root";
    dirCrt = dirRoot;
    pathCrt.push_back("root");

    /* Check the file. */
    string opt;
    FILE *test = fopen("../dat/explorerdat.txt", "r");
    if (test == NULL)
    {
        return 0;
    }
    fclose(test);

    /* Get data. */
    ifstream fin("../dat/explorerdat.txt");
    while (fin >> opt)
    {
        if (opt == "md") //Create a child directory.
        {
            string name;
            fin >> name;
            if (!createNewDir(name))
            {
                fin.close();
                return 0;
            }
        }
        else if (opt == "mf") //Create a new file.
        {
            string name, type;
            fin >> name >> type;
            if (!createNewFile(name, type))
            {
                fin.close();
                return 0;
            }
        }
        else if (opt == "cd") //Move to a directory.
        {
            string name;
            fin >> name;
            if (!goToDir(name))
            {
                fin.close();
                return 0;
            }
        }
    }
    fin.close();
    return 1; //Succeeded.
}
