#ifndef COM_BG
#define COM_BG

#include "global.h"

int call_bg()
{
    if (numargs != 2)
    {
        printf("%s: invalid number of arguments\n", commands[0]);
        return 0;
    }
    if (str_is_num(commands[1]) == 0)
    {

        printf("%s: invalid argument\n", commands[0]);
        return 0;
    }
    int arg1 = my_atoi(commands[1]);
    if (arg1 > bgcommands_num || arg1 == 0)
    {
        printf("%s: no such job\n", commands[0]);
        return 0;
    }
    if (getpgid(bgprocesses_ID[arg1 - 1]) >= 0)
    {
        if (kill(bgprocesses_ID[arg1 - 1], 18) >= 0)
            return 1;
    }
    else
    {
        printf("Process has been terminated.\n");
    }
    return 0;
}

#endif