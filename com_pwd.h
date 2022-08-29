#ifndef COM_PWD_H
#define COM_PWD_H
#include "global.h"

int call_pwd()
{
    if (numargs > 1)
    {
        printf("pwd: Too many arguments\n");
        return 0;
    }
    struct utsname xname;
    uname(&xname);
    char currdirname[1000];
    char *result = getcwd(currdirname, sizeof(currdirname));
    printf("%s\n", currdirname);
    return 1;
}
#endif