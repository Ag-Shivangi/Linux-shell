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
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <grp.h>
#include <signal.h>

char shelldir[1000];
int Shell_Id;
const char *DELIMITER = " \t\r\n\a";
char months[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
const int MAX_ARGUMENTS = 1024;
int numargs;
int numcommands;
int curFgProc;
char **commands;
char **allCommands;
char lastpwd[1000];
char *history[20];
int first_hist, size_hist;
int bgcommands_num = 0;
int bgprocesses_ID[1000];
char bgprocesses_name[1000][1000];
time_t start_sec = 0, end_Sec = 0;
int kb_interrupt = 0;
int copyOfStdIn;
int changedStdIn;
int changedStdOut;
int copyOfStdOut;

void prompt();

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

int string_contains(char *strtarget, char *strfind)
{
    int n = strlen(strtarget);
    int m = strlen(strfind);
    if (m == 0)
        return 1;
    for (int i = 0; i < n; i++)
    {
        int contains = 1;
        for (int j = 0; j < m; j++)
        {
            if (i + j >= n)
            {
                contains = 0;
                break;
            }
            if (strtarget[i + j] != strfind[j])
            {
                contains = 0;
                break;
            }
        }
        if (contains)
            return 1;
    }
    return 0;
}

void string_reverse(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        char tmp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = tmp;
    }
}
#endif