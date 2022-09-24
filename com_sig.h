#ifndef COM_SIG
#define COM_SIG

#include "global.h"

int call_sig()
{
    if (numargs != 3)
    {
        printf("%s: invalid number of arguments\n", commands[0]);
        return 0;
    }

    if (str_is_num(commands[1]) == 0)
    {
        printf("%s: invalid argument %s\n", commands[0], commands[1]);
        return 0;
    }
    if (str_is_num(commands[2]) == 0)
    {
        printf("%s: invalid argument %s\n", commands[0], commands[2]);
        return 0;
    }

    int arg1 = my_atoi(commands[1]);
    int arg2 = my_atoi(commands[2]);
    if (bgcommands_num < arg1 || arg1 == 0)
    {
        printf("%s: no such job\n", commands[0]);
        return 1;
    }
    if (getpgid(bgprocesses_ID[arg1 - 1]) >= 0)
        kill(bgprocesses_ID[arg1 - 1], arg2);
    else
        printf("Process has been terminated.\n");
    return 1;
}

#endif