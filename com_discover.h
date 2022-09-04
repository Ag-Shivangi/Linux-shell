#ifndef COM_DISCO_H
#define COM_DISCO_H

#include "global.h"

int find(char *toFind, char *dirPath, int flagD, int flagF)
{
    // printf("opening %s\n", dirPath);
    DIR *dir = opendir(dirPath);
    if (dir == NULL)
    {
        perror("discover");
        return 0;
    }
    struct dirent *fileHere = readdir(dir);
    while (fileHere != NULL)
    {
        // if -d flag is there, iterate over all the directories
        // in dir and check if toFind is in the name or not
        if (flagD && fileHere->d_type == DT_DIR)
        {
            char *here = malloc(1000 * sizeof(char));
            here[0] = '\0';
            strcat(here, dirPath);
            strcat(here, "/");
            strcat(here, fileHere->d_name);
            if (string_contains(here, toFind))
            {
                printf("%s/%s\n", dirPath, fileHere->d_name);
            }
            free(here);
        }
        // if - f flag is there, iterate over all the files in dir
        // and check if toFind is in the name or not
        if (flagF && fileHere->d_type == DT_REG)
        {
            char *here = malloc(1000 * sizeof(char));
            here[0] = '\0';
            strcat(here, dirPath);
            strcat(here, "/");
            strcat(here, fileHere->d_name);
            if (string_contains(here, toFind))
            {
                printf("%s/%s\n", dirPath, fileHere->d_name);
            }
            free(here);
            // printf("%s/%s\n", dirPath, fileHere->d_name);
        }
        fileHere = readdir(dir);
    }

    // call find(dir->childDirectory, toFind) for all the directories in dir
    // printf("rewind?\n");
    rewinddir(dir);
    fileHere = readdir(dir);
    while (fileHere != NULL)
    {
        // printf("reading %s\n", fileHere->d_name);
        if (fileHere->d_name[0] != '.' && fileHere->d_type == DT_DIR)
        {
            // printf("from %s ", toFind);
            int len_here = strlen(dirPath);
            strcat(dirPath, "/");
            strcat(dirPath, fileHere->d_name);
            // printf(" calling %s\n", toFind);
            find(toFind, dirPath, flagD, flagF);
            dirPath[len_here] = '\0';
        }
        fileHere = readdir(dir);
    }
    return 1;
}

void assignFlags(int idx, int *flagF, int *flagD, int *wrongFlag)
{
    for (int i = 1; i < strlen(commands[idx]); i++)
    {
        if (commands[idx][i] == 'f')
            *flagF = 1;
        else if (commands[idx][i] == 'd')
            *flagD = 1;
        else
            *wrongFlag = 1;
    }
}

int call_discover()
{
    if (numargs == 1)
    {
        return find("", ".", 1, 1);
    }
    else if (numargs == 2)
    {
        if (commands[1][0] == '-')
        {
            if (strlen(commands[1]) == 1)
            {
                printf("discover: incorrect flag provided\n");
                return 0;
            }
            int flagF = 0, flagD = 0, wrongFlag = 0;
            assignFlags(1, &flagF, &flagD, &wrongFlag);
            if (wrongFlag)
            {
                printf("discover: incorrect flag provided\n");
                return 0;
            }
            return find("", ".", flagD, flagF);
        }
        else
        {
            // if only 1 non flag is providwed, it is the path
            return find("", commands[1], 1, 1);
        }
    }
    else
    {
        char *pathDir = NULL, *toFind = NULL;
        int gotFlag = 0;
        int flagF = 0, flagD = 0, wrongFlag = 0;
        int gotFind = 0;
        for (int i = 1; i < numargs; i++)
        {
            if (commands[i][0] == '-')
            {
                gotFlag = 1;
                assignFlags(i, &flagF, &flagD, &wrongFlag);
            }
            else if (gotFlag || pathDir != NULL)
            {
                if (!gotFind)
                {
                    gotFind = 1;
                    toFind = (char *)malloc(1000 * sizeof(char));
                    // toFind = commands[i];
                    strcpy(toFind, commands[i]);
                }
                else
                {
                    printf("discover: incorrect format\n");
                    return 0;
                }
            }
            else
            {
                pathDir = (char *)malloc(1000 * sizeof(char));
                // pathDir = commands[i];
                strcpy(pathDir, commands[i]);
            }
        }
        if (wrongFlag)
        {
            printf("discover: wrong flags\n");
            return 0;
        }
        if (toFind == NULL)
        {
            toFind = (char *)malloc(10 * sizeof(char));
            toFind[0] = '\0';
        }
        if (pathDir == NULL)
        {
            pathDir = (char *)malloc(10 * sizeof(char));
            pathDir[0] = '.';
            pathDir[1] = '\0';
        }
        if (flagF == 0 && flagD == 0)
        {
            flagF = flagD = 1;
        }
        return find(toFind, pathDir, flagD, flagF);
    }
    return 0;
}

#endif