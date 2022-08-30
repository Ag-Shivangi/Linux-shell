#ifndef COM_ECHO_H
#define COM_ECHO_H
#include "global.h"

int call_echo()
{
    // prints the token separated by a " "
    for (int i = 1; i < numargs; i++)
    {
        printf("%s ", commands[i]);
    }
    printf("\n");
    return 1;
}
#endif