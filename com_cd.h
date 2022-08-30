#ifndef COM_CD_H
#define COM_CD_H
#include "global.h"

int call_cd()
{
    if (numargs > 2)
    {
        printf("cd: Too many arguments\n");
        return 0;
    }
    char temppwd[1000];
    strcpy(temppwd, lastpwd);
    struct utsname xname;
    uname(&xname);
    char *result = getcwd(lastpwd, sizeof(lastpwd));
    if (numargs == 1)
    {
        int ret = chdir(shelldir);
        if (ret == -1)
        {
            perror("cd");
            return 0;
        }

        return 1;
    }
    // ~ flag for cd
    if (commands[1][0] == '~')
    {
        chdir(shelldir);
        if (strlen(commands[1]) > 2)
        {
            commands[1]++;
            commands[1]++;
        }
        else
        {
            return 1;
        }
    }
    // - flag for cd
    if (strcmp(commands[1], "-") == 0)
    {
        chdir(temppwd);
        return 1;
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