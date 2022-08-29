#ifndef COM_ECHO_H
#define COM_ECHO_H
#include "global.h"

int call_echo()
{
    for (int i = 1; i < numargs; i++)
    {
        printf("%s ", commands[i]);
    }
    printf("\n");
    return 1;
}
#endif