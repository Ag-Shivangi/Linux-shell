#ifndef INPUT_H
#define INPUT_H
#include "global.h"

char *readLine()
{
    char *ret = (char *)malloc(1000 * sizeof(char));
    size_t len = 1000;
    if (getline(&ret, &len, stdin) == -1)
    {
        printf("quit\n");
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

#endif