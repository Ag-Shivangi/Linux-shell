#ifndef COM_PINFO_H
#define COM_PINFO_H
#include "global.h"
int doesexist()
{
    char processFile[1500] = "/proc/";
    processFile[6] = '\0';
    strcat(processFile, commands[1]);
    processFile[7 + strlen(commands[1])] = '\0';
    struct stat stats;
    if (stat(processFile, &stats) < 0 && errno == ENOENT)
    {
        return 0;
    }
    return 1;
}
int check_for_plus(char *line)
{
    char fourword[1000] = {'\0'};
    int count = 0, j = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == ' ')
            count++;
        if (count == 4)
            break;
        if (count == 4 - 1)
            fourword[j++] = line[i];
    }
    char sevenword[1000] = {'\0'};
    count = 0;
    j = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == ' ')
            count++;
        if (count == 7)
            break;
        if (count == 7 - 1)
            sevenword[j++] = line[i];
    }
    // printf("+%s+\n +%s+\n", fourword, sevenword);
    if (strcmp(sevenword, fourword) == 0)
    {
        return 1;
    }
    return 0;
}
void nwordfun(char *line, int n)
{
    char nword[1000] = {'\0'};
    int count = 0, j = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == ' ')
            count++;
        if (count == n)
            break;
        if (count == n - 1)
            nword[j++] = line[i];
    }
    if (n == 3)
    {
        if (check_for_plus(line) == 1)
        {
            printf("%s+\n", nword);
            return;
        }
    }
    printf("%s\n", nword);
    return;
}
int call_pinfo()
{
    char processFile[1500] = "/proc/";
    processFile[6] = '\0';
    if (numargs == 2)
    {
        //( check if process exists
        if (doesexist() == 0)
        {
            printf("Process with pid %s does not exist\n", commands[1]);
            return 1;
        }
        printf("pid  :  %s\n", commands[1]);
        strcat(processFile, commands[1]);
        processFile[7 + strlen(commands[1])] = '\0';
    }
    else if (numargs > 2)
    {
        perror("pinfo: Too many arguments");
        return 0;
    }
    else
    {
        printf("pid  :  %d\n", Shell_Id);
        char *tempshellid = my_itoa(Shell_Id);
        strcat(processFile, tempshellid);
        processFile[7 + strlen(tempshellid)] = '\0';
    }
    strcat(processFile, "/stat");
    FILE *reader = fopen(processFile, "r");
    char line[10000];
    fgets(line, 10000, reader);
    printf("process Status  :  ");
    nwordfun(line, 3);
    printf("memory  :  ");
    nwordfun(line, 23);
    processFile[strlen(processFile) - 1] = '\0';
    processFile[strlen(processFile) - 1] = processFile[strlen(processFile) - 3] = 'e';
    processFile[strlen(processFile) - 2] = 'x';
    char newline[10000] = {'\0'};
    readlink(processFile, newline, 10000);
    if (strncmp(newline, shelldir, strlen(shelldir)) == 0)
    {
        newline[0] = '~';
        int len_line = strlen(newline);
        for (int i = strlen(shelldir); i < len_line; i++)
        {
            newline[i - strlen(shelldir) + 1] = newline[i];
        }
        for (int i = len_line - strlen(shelldir) + 1; i < len_line; i++)
        {
            newline[i] = '\0';
        }
    }
    printf("executable Path  :  %s\n", newline);
    return 1;
}
#endif