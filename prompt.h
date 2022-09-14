#ifndef PROMPT_H
#define PROMPT_H
#include "global.h"

void currwd()
{
    struct utsname xname;
    uname(&xname);
    char currdirname[1000];
    char *result = getcwd(currdirname, sizeof(currdirname));

    int cflag = 0;
    if (strlen(currdirname) < strlen(shelldir))
        cflag = 1;
    else
    {
        for (int i = 0; i < strlen(shelldir); i++)
            if (shelldir[i] != currdirname[i])
            {
                cflag = 1;
                break;
            }
    }
    if (cflag == 1)
        printf("%s", currdirname);
    else
    {
        printf("~");
        for (int i = strlen(shelldir); i < strlen(currdirname); i++)
            printf("%c", currdirname[i]);
    }
}

void prompt()
{
    struct utsname xname;
    uname(&xname);
    struct passwd *p = getpwuid(getuid());
    size_t username_size, hostname_size;
    char *username = p->pw_name;
    char *hostname = xname.nodename;
    printf("\033[0;32m"); // prints in green
    printf("<%s@%s", username, hostname);
    printf("\033[0;33m"); // prints in yellow
    printf(":");
    currwd();
    if (end_Sec - start_sec >= 1)
    {
        printf("took %lds", end_Sec - start_sec);
    }
    start_sec = 0;
    end_Sec = 0;
    printf("> ");
    printf("\033[0m"); // resets stdout color
}

#endif