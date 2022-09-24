
#include "global.h"
#include "input_manipulation.h"
#include "com_cd.h"
#include "exit.h"
#include "initial.h"
#include "com_echo.h"
#include "com_jobs.h"
#include "com_ls.h"
#include "com_history.h"
#include "com_pwd.h"
#include "com_pinfo.h"
#include "com_discover.h"
#include "com_sig.h"
#include "com_fg.h"
#include "foregroundprocess.h"
#include "backgroundprocess.h"
#include "signalhandle.h"
#include "prompt.h"

int main()
{
    initfun(); // initializes shelldir, history
    char input[1000];
    char tmp[1000];
    signal(SIGINT, Handle_SIGINT);
    signal(SIGTSTP, Handle_SIGSTP);
    while (1)
    {
        prompt(); // prints username, hostname and path
        strcpy(input, readLine());
        strcpy(tmp, input);
        int iscopy = strcmp(tmp, history[(size_hist + 19) % 20]);
        char **commandsHere = separateCommands(input);
        for (int i = 0; i < numcommands; i++)
        {
            commands = separateInput(commandsHere[i]);
            if (numargs == 0)
                continue;
            if (i == 0 & iscopy != 0)
            {
                strcpy(history[(size_hist) % 20], tmp);
                size_hist++;
                if (size_hist > 20)
                {
                    first_hist = (first_hist + 1) % 20;
                }
            }
            if (checkForInputFile() < 0)
            {
                continue;
            }
            if (checkForOutputFile() < 0)
            {
                continue;
            }
            int check;
            // checking bg process
            if (strcmp(commands[numargs - 1], "&") == 0)
            {
                check = bgproc();
                continue;
            }
            // command identifier
            if (strcmp(commands[0], "exit") == 0)
            {
                exit_fun();
                free(commands);
                free(commandsHere);
                return 0;
            }
            else if (strcmp(commands[0], "cd") == 0)
            {
                check = call_cd();
            }
            else if (strcmp(commands[0], "pwd") == 0)
            {
                check = call_pwd();
            }
            else if (strcmp(commands[0], "pinfo") == 0)
            {
                check = call_pinfo();
            }
            else if (strcmp(commands[0], "ls") == 0)
            {
                check = call_ls();
                printf("\033[0m"); // resets stdout color
            }
            else if (strcmp(commands[0], "history") == 0)
            {
                check = call_history();
            }
            else if (strcmp(commands[0], "discover") == 0)
            {
                check = call_discover();
            }
            else if (strcmp(commands[0], "echo") == 0)
            {
                check = call_echo();
            }
            else if (strcmp(commands[0], "jobs") == 0)
            {
                check = call_jobs();
            }
            else if (strcmp(commands[0], "sig") == 0)
            {
                check = call_sig();
            }
            else if (strcasecmp(commands[0], "fg") == 0)
            {
                check = call_fg();
            }
            else if (strcmp(commands[0], "\n"))
            {
                check = fgProc();
                // printf("%s: command not found\n", commands[0]);
            }
            free(commands);
            if (changedStdIn)
            {
                resetFiles(copyOfStdIn, 0, &changedStdIn);
            }
            if (changedStdOut)
            {
                resetFiles(copyOfStdOut, 1, &changedStdOut);
            }
        }
        free(commandsHere);
    }
    return 0;
}