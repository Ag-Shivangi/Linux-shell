#ifndef COM_FG
#define COM_FG

#include "global.h"

int call_fg()
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
    __pid_t pid = getpgid(bgprocesses_ID[arg1 - 1]);
    if (pid >= 0)
    {
        kill(bgprocesses_ID[arg1 - 1], SIGCONT);
        tcsetpgrp(0, pid);
        signal(22, (__sighandler_t)1);
        signal(21, (__sighandler_t)1);
        int x = waitpid(pid, NULL, WUNTRACED);
        tcsetpgrp(0, getpgid(Shell_Id));
        signal(22, ((__sighandler_t)0));
        signal(21, ((__sighandler_t)0));
        if (x == -1)
        {
            return 0;
        }
    }
    else
    {
        printf("Process has been terminated.\n");
        return 0;
    }
    return 1;
}

#endif