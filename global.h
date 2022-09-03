#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <grp.h>

char shelldir[1000];
int Shell_Id;
const char *DELIMITER = " \t\r\n\a";
char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
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

void string_prepend(char *s, char *suffix)
{
    char temp[2000] = {'\0'};
    for (int i = 0; i < strlen(suffix); i++)
    {
        temp[i] = suffix[i];
    }
    for (int i = 0; i < strlen(s); i++)
    {
        temp[i + strlen(suffix)] = s[i];
    }
    for (int i = 0; i < strlen(temp); i++)
    {
        s[i] = temp[i];
    }
}

void remove_suffix(char *s, int n)
{
    int len = strlen(s);
    for (int i = 0; i + n < len; i++)
        s[i] = s[i + n];
    for (int i = strlen(s) - n; i < len; i++)
        s[i] = '\0';
}
#endif