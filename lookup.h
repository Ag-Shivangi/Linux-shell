#ifndef LOOKUP
#define LOOKUP

#include "global.h"

#include "com_cd.h"
#include "com_echo.h"
#include "com_jobs.h"
#include "com_ls.h"
#include "com_history.h"
#include "com_pwd.h"
#include "com_pinfo.h"
#include "com_discover.h"
#include "com_sig.h"
#include "com_fg.h"
#include "com_bg.h"
#include "foregroundprocess.h"
#include "backgroundprocess.h"

int lookup()
{
    // int check;
    // checking bg process
    if (strcmp(commands[numargs - 1], "&") == 0)
    {
        check = bgproc();
        return 1;
    }
    // command identifier
    if (strcmp(commands[0], "exit") == 0)
    {
        exit_fun();
        free(commands);
        free(commandsHere);
        exit(0);
    }
    else if (strcmp(commands[0], "cd") == 0)
    {
        check = call_cd();
    }
    else if (strcmp(commands[0], "pwd") == 0)
    {
        check = call_pwd();
    }
    else if (strcmp(commands[0], "pinfo") == 0)
    {
        check = call_pinfo();
    }
    else if (strcmp(commands[0], "ls") == 0)
    {
        check = call_ls();
        printf("\033[0m"); // resets stdout color
    }
    else if (strcmp(commands[0], "history") == 0)
    {
        check = call_history();
    }
    else if (strcmp(commands[0], "discover") == 0)
    {
        check = call_discover();
    }
    else if (strcmp(commands[0], "echo") == 0)
    {
        check = call_echo();
    }
    else if (strcmp(commands[0], "jobs") == 0)
    {
        check = call_jobs();
    }
    else if (strcmp(commands[0], "sig") == 0)
    {
        check = call_sig();
    }
    else if (strcasecmp(commands[0], "fg") == 0)
    {
        check = call_fg();
    }
    else if (strcmp(commands[0], "bg") == 0)
    {
        check = call_bg();
    }
    else if (strcmp(commands[0], "\n"))
    {
        check = fgProc();
        // printf("%s: command not found\n", commands[0]);
    }
    return check;
}

#endif