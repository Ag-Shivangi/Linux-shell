#ifndef BG_PROC
#define BG_PROC
#include "global.h"

void processEnd()
{
    for (int a = 0; a < bgcommands_num; a++)
    {
        int status;
        int flags = (1 | 2);
        int x = waitpid(bgprocesses_ID[a], &status, flags);
        if (x > 0)
        {
            char mesg[1000];
            mesg[0] = '[';
            mesg[1] = '\0';
            strcat(mesg, my_itoa(a + 1));
            strcat(mesg, "] ");
            strcat(mesg, bgprocesses_name[a]);
            strcat(mesg, " with pid ");
            strcat(mesg, my_itoa(bgprocesses_ID[a]));
            if (WIFEXITED(status) > 0)
            {
                strcat(mesg, " normally");
            }
            else if (WIFEXITED(status))
            {
                strcat(mesg, " with status ");
                strcat(mesg, my_itoa(status));
            }
            else
            {
                strcat(mesg, " abnormally");
            }
            printf("%s\n", mesg);
        }
    }
}
int bgproc()
{
    signal(SIGCHLD, processEnd);
    pid_t flag = fork();
    if (flag < 0) // no process
    {
        printf("%s: could not fork child\n", commands[0]);
        return 0;
    }
    if (flag) // parent process
    {
        bgprocesses_ID[bgcommands_num] = flag;
        strcpy(bgprocesses_name[bgcommands_num], commands[0]);
        bgcommands_num++;
        char temp[2000];
        temp[0] = '[';
        temp[1] = '\0';
        strcat(temp, my_itoa(bgcommands_num));
        strcat(temp, "] ");
        strcat(temp, my_itoa(flag));
        printf("%s\n", temp);
    }
    else // child process
    {

        commands[numargs - 1] = NULL;
        numargs--;
        int checkchild = setpgid(getpid(), 0);
        int checkbgcom = execvp(commands[0], commands);
        if (checkbgcom < 0)
        {
            printf("%s: command not found\n", commands[0]);
            exit(1);
        }
        exit(0);
    }
    return 1;
}
#endif