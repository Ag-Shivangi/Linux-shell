#ifndef COM_CD_H
#define COM_CD_H
#include "global.h"
#include <stdio.h>
#include <unistd.h>

int call_cd()
{
    if (numargs != 2)
    {
        printf("cd: Too many arguments");
        return 0;
    }
    int ret = chdir(commands[1]);
    if (ret == -1)
    {
        perror("cd");
        return 0;
    }
    return 1;
}
#endif