#ifndef FG_PROC
#define FG_PROC
#include "global.h"
int fork_fun_proc(int flag)
{
    curFgProc = flag;
    int status, ret;
    pid_t pflag = getpgid(flag);
    signal(22, SIG_IGN); // write to ctrl terminal
    signal(21, SIG_IGN); // read to ctrl terminal
    tcsetpgrp(0, pflag);
    if (waitpid(flag, &status, WUNTRACED) == -1)
    {
        return 0;
    }
    pid_t shellflag = getpgid(Shell_Id);
    tcsetpgrp(0, shellflag);
    // default
    signal(22, SIG_DFL); // write ctrl back to terminal
    signal(21, SIG_DFL); // read ctrl back to terminal
    return 1;
}
int fgProc()
{
    pid_t flag = fork();
    if (flag < 0) // no process
    {
        printf("%s: could not fork child\n", commands[0]);
        return 0;
    }
    if (flag) // process. yes.
    {
        int fgproc_check = fork_fun_proc(flag);
        curFgProc = Shell_Id;
        return (fgproc_check);
    }
    else // child process
    {
        commands[numargs] = NULL;
        int checkchild = execvp(commands[0], commands);
        if (checkchild < 0)
        {
            printf("%s: No such command exists \n", commands[0]);
            raise(17);
            _exit(1);
        }
        exit(0);
    }
    return 1;
}

#endif