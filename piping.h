#ifndef PIPING
#define PIPING

#include "global.h"
#include "lookup.h"

int checkpipes()
{
    int found = 0;
    for (int i = 0; i < numargs; i++)
    {
        if (strcmp(commands[i], "|") == 0)
        {
            found = 1;
        }
    }
    return found;
}

void copyfd(int arg1, int arg2)
{
    dup2(arg1, arg2);
    close(arg1);
}

void singlepipecommand(int in, int out)
{
    pid_t pid;
    if ((pid = fork()) == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        commands[numargs] = NULL;
        if (out != 1)
        {
            copyfd(out, 1);
        }
        if (in != 0)
        {
            copyfd(in, 0);
        }
        lookup();
        exit(0);
    }
    else
    {
        if (waitpid(pid, NULL, WUNTRACED) == -1)
        {
            check = 0;
        }
        else
        {
            check = 1;
        }
    }
}

void handlepipes()
{
    char **tmpcommands = commands;
    int totalargs = numargs, fd[2], in = 0;
    numargs = 1;
    int doLast = 1;
    for (int i = 1; i < totalargs; i++)
    {
        if (strcmp(tmpcommands[i], "|") != 0)
        {
            numargs += 1;
        }
        else
        {
            i++;
            pipe(fd);
            singlepipecommand(in, fd[1]);
            close(fd[1]);
            in = fd[0];
            numargs++;
            commands += numargs;
            numargs = 1;
        }
        if (check == 0)
        {
            doLast = 0;
            break;
        }
    }
    if (doLast)
    {
        singlepipecommand(in, 1);
    }
    commands = tmpcommands;
    numargs = totalargs;
}

#endif