#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <sys/stat.h>

char shelldir[1000];
int Shell_Id;
const char *DELIMITER = " \t\r\n\a";
const int MAX_ARGUMENTS = 1024;
int numargs;
int numcommands;
int curCommandBg;
char **commands;
char **allCommands;
char lastpwd[1000];
char *history[20];
int first_hist, size_hist;

char *my_itoa(int val)
{
    static char buf[32] = {0};
    int i = 30;
    for (; val && i; --i, val /= 10)
    {
        buf[i] = "0123456789abcdef"[val % 10];
    }
    return &buf[i + 1];
}
#endif