#ifndef INPUT_H
#define INPUT_H
#include "global.h"

char *readLine()
{
    char *ret = (char *)malloc(1000 * sizeof(char));
    size_t len = 1000;
    if (getline(&ret, &len, stdin) == -1)
    {
        printf("Exiting terminal\n");
        exit_fun();
        _exit(2);
    }
    return ret;
}

// Separates tokens of a command (removes spaces enter etc)
char **separateInput(char *line)
{
    char **ret = (char **)malloc(MAX_ARGUMENTS * sizeof(char *));
    char *arg;
    numargs = 0;
    arg = strtok(line, DELIMITER);
    while (arg != NULL)
    {
        ret[numargs] = arg;
        numargs++;
        arg = strtok(NULL, DELIMITER);
    }
    ret[numargs] = arg;
    return ret;
}

// separates commands of an input (;)
char **separateCommands(char *line)
{
    char **ret = (char **)malloc(MAX_ARGUMENTS * sizeof(char *));
    char *arg;
    const char x[] = ";";
    numcommands = 0;
    arg = strtok(line, x);
    while (arg != NULL)
    {
        ret[numcommands] = arg;
        numcommands++;
        arg = strtok(NULL, x);
    }
    ret[numcommands] = arg;
    return ret;
}

int openInputFile(int idx)
{
    char fileName[1000];
    int copyIdx = idx;
    int startIdx = 1;
    if (strlen(commands[idx]) == 1)
    {
        copyIdx = idx + 1;
        startIdx = 0;
    }
    if (copyIdx >= numargs)
    {
        return -1;
    }
    for (int i = startIdx; i < strlen(commands[copyIdx]); i++)
        fileName[i - startIdx] = commands[copyIdx][i];
    fileName[strlen(commands[copyIdx]) - startIdx] = '\0';
    if (copyIdx == idx)
    {
        for (int i = idx; i < numargs - 1; i++)
            commands[i] = commands[i + 1];
        numargs--;
        commands[numargs] = NULL;
    }
    else
    {
        for (int i = idx; i < numargs - 2; i++)
            commands[i] = commands[i + 2];
        numargs--;
        commands[numargs] = NULL;
        numargs--;
        commands[numargs] = NULL;
    }
    int fd;
    if ((fd = open(fileName, O_RDONLY)) == -1)
    {
        perror("File error");
        return -1;
    }
    copyOfStdIn = dup(0);
    dup2(fd, 0);
    changedStdIn = 1;
    return 1;
}

int checkForInputFile()
{
    // return 0 if no input file, return 1 otherwise
    for (int i = 1; i < numargs; i++)
    {
        if (commands[i][0] == '<')
        {
            return openInputFile(i);
        }
    }
    return 0;
}

void resetFiles(int to, int from, int *flag)
{
    dup2(to, from); // for example, call resetFiles(copyOfStdIn, 0, &changedStdIn)
    *flag = 0;
}

int openOutputFile(int idx)
{
    char fileName[1000];
    int overwrite = 1;
    // int overwrite=wora();
    int copyIdx = idx;
    int startIdx = 1;
    /*
    1. > filename <- handled in first if
    2. >filename <- default case
    3. >> filename
    4. >>filename
    */
    if (strlen(commands[idx]) == 1)
    {
        // case 1
        copyIdx = idx + 1;
        startIdx = 0;
        overwrite = 1;
    }
    else
    {
        if (strlen(commands[idx]) == 2 && commands[idx][1] == '>')
        {
            // case 3
            startIdx = 0;
            overwrite = 0;
            copyIdx = idx + 1;
        }
        else if (strlen(commands[idx]) > 2 && commands[idx][1] == '>')
        {
            // case 4
            startIdx = 2;
            overwrite = 0;
            copyIdx = idx;
        }
    }
    if (copyIdx >= numargs)
    {
        return -1;
    }
    for (int i = startIdx; i < strlen(commands[copyIdx]); i++)
        fileName[i - startIdx] = commands[copyIdx][i];
    fileName[strlen(commands[copyIdx]) - startIdx] = '\0';
    if (copyIdx == idx)
    {
        for (int i = idx; i < numargs - 1; i++)
            commands[i] = commands[i + 1];
        numargs--;
        commands[numargs] = NULL;
    }
    else
    {
        for (int i = idx; i < numargs - 2; i++)
            commands[i] = commands[i + 2];
        numargs--;
        commands[numargs] = NULL;
        numargs--;
        commands[numargs] = NULL;
    }
    int fd;
    if (overwrite)
    {
        if ((fd = open(fileName, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        {
            perror("File error");
            return -1;
        }
    }
    else
    {
        if ((fd = open(fileName, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
        {
            perror("File error");
            return -1;
        }
    }
    copyOfStdOut = dup(1);
    dup2(fd, 1);
    changedStdOut = 1;
    return 1;
}

int checkForOutputFile()
{
    // return 0 if no input file, return 1 otherwise
    for (int i = 1; i < numargs; i++)
    {
        if (commands[i][0] == '>')
        {
            return openOutputFile(i);
        }
    }
    return 0;
}

#endif