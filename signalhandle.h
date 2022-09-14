#ifndef SIGNAL_H
#define SIGNAL_H
#include "global.h"

// ctrl+c
void Handle_SIGINT()
{
    while (curFgProc != Shell_Id)
    {
        kill(curFgProc, SIGINT);
        curFgProc = Shell_Id;
        kb_interrupt = 1;
    }
    printf("\n");
}

// ctrl+z
void Handle_SIGSTP()
{
    if (curFgProc != Shell_Id)
    {
        printf("\n");
        bgprocesses_ID[bgcommands_num] = curFgProc;
        strncpy(bgprocesses_name[bgcommands_num], commands[0], strlen(commands[0]));
        kill(curFgProc, SIGTSTP);
        curFgProc = Shell_Id;
        kb_interrupt = 1;
        printf("[%d] Stopped\n", ++bgcommands_num);
    }
}
#endif