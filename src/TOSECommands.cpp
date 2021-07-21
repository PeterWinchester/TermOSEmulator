/*
 * TOSECommands.cpp
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

#include "TOSECommands.h"

CmdFunc cmdOpt[NUM_COMMANDS] = {
    pause, exitSys, ls, cd, mkdir, rmdir, view, help, apt, rmf};

string cmdName[NUM_COMMANDS] = {
    "pause", "exit", "ls", "cd", "mkdir", "rmdir", "view", "help", "apt", "rmf"};

int pause(vector<string> args)
{
    /* Check parameters. */
    if (args.size())
    {
        printf("The command 'pause' doesn't need any parameter.\n");
        return 0; //Failed.
    }
    /* Pause. */
    printf("Press any key to continue...");
    getch();
    printf("\n");
    return 1; //Success.
}

int exitSys(vector<string> args)
{
    /* Check parameters. */
    if (args.size())
    {
        printf("The command 'exit' doesn't need any parameter.\n");
        return 0; //Failed.
    }
    /* Exit. */
    toseRunning = false; //This means TOSE will quit!
    return 1;            //Success.
}

int ls(vector<string> args)
{
    /* Check the parameters. */
    if (args.size())
    {
        printf("The command 'ls' doesn't need any parameter.\n");
        return 0; //Failed.
    }
    /* Work. */
    /* If the current directory is not /, there is a father directory. */
    if (dirCrt != dirRoot)
    {
        color(9);
        printf(".. ");
        color(7);
    }
    /* Show child directories. */
    color(9);
    for (int i = 0; i < dirCrt->dirChild.size(); i++)
    {
        cout << dirCrt->dirChild[i]->name << " ";
        if ((i + 1) % 5 == 0)
            printf("\n");
    }
    /* Show files. */
    color(7);
    for (int i = 0; i < dirCrt->file.size(); i++)
    {
        if (dirCrt->file[i].type == "exe") //Executable file.
        {
            color(10);
            cout << dirCrt->file[i].name << "." << dirCrt->file[i].type << " ";
            color(7);
        }
        else
        {
            cout << dirCrt->file[i].name << "." << dirCrt->file[i].type << " ";
        }
        if ((i + 1) % 5 == 0)
            printf("\n");
    }
    cout << endl;
    return 1; //Success.
}

int cd(vector<string> args)
{
    /* Check parameters. This command needs one parameter. */
    if (args.size() == 0)
    {
        printf("The command 'cd' needs a parameter.\n");
        printf("Type 'help cd' for help.\n");
        return 0; //Failed.
    }
    if (args.size() > 1)
    {
        printf("The parameters are too many.\n");
        printf("Type 'help cd' for help.\n");
        return 0; //Failed.
    }
    /* Work. */
    if (!goToDir(args[0]))
    {
        printf("Directory not found.\n");
        return 0; //Failed.
    }
    return 1; //Success.
}

int mkdir(vector<string> args)
{
    /* Check the parameters. This command needs one parameter. */
    if (args.size() == 0)
    {
        printf("The command 'mkdir' needs a parameter.\n");
        printf("Type 'help mkdir' for help.\n");
        return 0; //Failed.
    }
    if (args.size() > 1)
    {
        printf("The parameters are too many.\n");
        printf("Type 'help mkdir' for help.\n");
        return 0; //Failed.
    }
    /* Work. */
    if (!createNewDir(args[0]))
    {
        return 0; //Failed.
    }
    return 1; //Failed.
}

int rmdir(vector<string> args)
{
    /* Check the parameters. This command needs one parameter. */
    if (args.size() == 0)
    {
        printf("The command 'rmdir' needs a parameter.\n");
        printf("Type 'help rmdir' for help.\n");
        return 0; //Failed.
    }
    if (args.size() > 1)
    {
        printf("The parameters are too many.\n");
        printf("Type 'help rmdir' for help.\n");
        return 0; //Failed.
    }
    /* Work. */
    /* Get the target path. */
    string dir;
    for (int i = 0; i < strlen(systemRootPath); i++)
    {
        dir.push_back(systemRootPath[i]);
    }
    for (int i = 1; i < pathCrt.size(); i++)
    {
        dir += pathCrt[i];
        dir += "/";
    }
    dir += args[0];
    dir += "/";
    /* Delete it on Windows. */
    if (!delDir(dir))
    {
        printf("Error! Please check the directory in Windows.\n");
        return 0;
    }
    /* Search for the directory. */
    for (int i = 0; i < dirCrt->dirChild.size(); i++)
    {
        if (dirCrt->dirChild[i]->name == args[0]) //Got it.
        {
            /* Delete it in TOSE. */
            for (int j = i; j < dirCrt->dirChild.size() - 1; j++)
            {
                dirCrt->dirChild[j] = dirCrt->dirChild[j + 1];
            }
            dirCrt->dirChild.pop_back();
            updateExplorer(); //Update the data of explorer.
            return 1;         //Success.
        }
    }
    printf("Error! Cannot find the directory.\n");
    return 0; //Failed.
}

int rmf(vector<string> args)
{
    /* Check the arguments. */
    if (args.size() == 0)
    {
        printf("The command 'rmf' needs a parameter.\n");
        printf("Type 'help rmf' for details.\n");
        return 0;
    }
    if (args.size() > 1)
    {
        printf("The parameters are too many.\n");
        printf("Type 'help rmf' for details.\n");
        return 0;
    }

    /* Get the type and the name. */
    string nameReq, typeReq;
    int pos = args[0].length() - 1;
    while (pos >= 0 & args[0][pos] != '.')
        pos--;
    for (int i = pos + 1; i < args[0].length(); i++)
        typeReq.push_back(args[0][i]);
    for (int i = 0; i < pos; i++)
        nameReq.push_back(args[0][i]);

    /* Check the file. */
    string dir;
    for (int i = 0; i < strlen(systemRootPath); i++)
    {
        dir.push_back(systemRootPath[i]);
    }
    for (int i = 1; i < pathCrt.size(); i++)
    {
        dir += pathCrt[i];
        dir += "/";
    }
    dir += args[0];
    FILE *find = fopen(dir.c_str(), "r");
    if (find == NULL)
    {
        printf("Can't find the file on Windows!\n");
        printf("Please check the current directory.\n");
        return 0;
    }
    fclose(find);
    if (!removeFile(nameReq, typeReq))
    {
        printf("Cannot find the file.\n");
        return 0;
    }

    /* Remove the file. */
    string cmd = "del \"";
    for (int i = 0; i < dir.length(); i++)
        if (dir[i] == '/')
            dir[i] = '\\';
    cmd += dir;
    cmd += "\"";
    int res = system(cmd.c_str());
    return res == 0;
}

int view(vector<string> args)
{
    /* Check the parameters. This command needs one parameter. */
    if (args.size() == 0)
    {
        printf("The command 'view' needs a parameter.\n");
        printf("Type 'help view' for help.\n");
        return 0; //Failed.
    }
    if (args.size() > 1)
    {
        printf("The parameters are too many.\n");
        printf("Type 'help view' for help.\n");
        return 0; //Failed.
    }
    /* Get the name and type of the target file. */
    string name = args[0], type;
    while (name.length() > 0 && name[name.length() - 1] != '.')
    {
        type.push_back(name[name.length() - 1]);
        name.pop_back();
    }
    name.pop_back();
    int l = 0, r = type.length() - 1;
    while (l < r)
    {
        swap(type[l], type[r]);
        l++, r--;
    }
    /* Search for target file. */
    bool find = false;
    for (int i = 0; i < dirCrt->file.size(); i++)
    {
        /* Got it. */
        if (dirCrt->file[i].name == name && dirCrt->file[i].type == type)
        {
            find = true;
            break;
        }
    }
    if (find == false) //Didn't find.
    {
        printf("Cannot find the file.\n");
        return 0; //Failed.
    }
    /* Get the directory in Windows. */
    string dir;
    for (int i = 0; i < strlen(systemRootPath); i++)
    {
        dir.push_back(systemRootPath[i]);
    }
    for (int i = 1; i < pathCrt.size(); i++)
    {
        dir += pathCrt[i];
        dir.push_back('/');
    }
    dir += name;
    dir.push_back('.');
    dir += type;
    /* Find the target file in Windows. */
    FILE *fin = fopen(dir.c_str(), "r");
    if (fin == NULL) //Cannot open the file.
    {
        printf("Error! Please check the file on Windows!\n");
        return 0; //Failed.
    }
    /* Read from the target file in Windows. */
    char cGet;
    while (fscanf(fin, "%c", &cGet) == 1)
    {
        /* The character '\r' needs to be processed specially. */
        if (cGet == '\r')
            printf("\n");
        else
            printf("%c", cGet);
    }
    fclose(fin);
    return 1; //Succeeded.
}

int help(vector<string> args)
{
    /*
      Check the parameters. This command is special,
      it can take no arguments. But if it takes one
      argument, the argument must be the name of a
      command.
    */
    if (args.size() == 0) //It takes no argument.
    {

        /* Get the directory in Windows. */
        string dir;
        for (int i = 0; i < strlen(systemRootPath); i++)
        {
            dir.push_back(systemRootPath[i]);
        }
        dir += "bin/help/help.txt";

        /* Find the help file. */
        FILE *fin = fopen(dir.c_str(), "r");
        if (fin == NULL) //File not found.
        {
            printf("Error! Help file ont found.\n");
            return 0; //Failed.
        }
        char cGet;
        while (fscanf(fin, "%c", &cGet) == 1)
        {
            /* Process '\r' specially. */
            if (cGet == '\r')
                printf("\n");
            else
                printf("%c", cGet);
        }
        fclose(fin);
        return 1; //Succeeded.
    }
    else if (args.size() == 1) //It takes one argument.
    {

        /* Get the directory. */
        string dir;
        for (int i = 0; i < strlen(systemRootPath); i++)
        {
            dir.push_back(systemRootPath[i]);
        }
        dir += "bin/help/";

        /* Search command. */
        bool find = false;
        for (int i = 0; i < NUM_COMMANDS; i++)
        {
            if (cmdName[i] == args[0])
            { //Got it.
                dir += args[0];
                dir += ".txt";
                find = true;
                break;
            }
        }
        if (!find) //Command not found.
        {
            printf("Error! Command '");
            cout << args[0];
            printf("' not found.\n");
            return 0; //Failed.
        }

        /* Find the file. */
        FILE *fin = fopen(dir.c_str(), "r");
        if (!fin) //File not found.
        {
            printf("Error! File not found.\n");
            return 0; //Failed.
        }
        char cGet;
        while (fscanf(fin, "%c", &cGet) == 1)
        {
            /* Process '\r' specially. */
            if (cGet == '\r')
                printf("\n");
            else
                printf("%c", cGet);
        }
        fclose(fin);
        return 1; //Succeeded.
    }
    printf("Error! The parameters are too many.\n");
    return 0; //Failed.
}

int apt(vector<string> args)
{

    /* Check the arguments. This function needs an argument. */
    if (args.size() == 0)
    {
        printf("Error! Command 'apt' needs an argument.\n");
        return 0;
    }
    if (args.size() > 1)
    {
        printf("Error! The parameters are too many.\n");
        return 0;
    }

    /* The number of arguments is right. */
    if (args[0] == "get")
    {
        return installApp();
    }
    else if (args[0] == "remove")
    {
        return removeApp();
    }
    else if (args[0] == "list")
    {
        return listApps();
    }
    else if (args[0] == "autoremove")
    {
        /* TODO: Process the argument "autoremove". */
		return autoRemove();
		
    }
    printf("The command 'apt' doesn't have the argument '");
    cout << args[0];
    printf("'.\n");
    return 0; //The argument is wrong, failed.
}
