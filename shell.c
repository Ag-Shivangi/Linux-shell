#include "global.h"
#include "input_manipulation.h"
#include "exit.h"
#include "initial.h"
#include "signalhandle.h"
#include "prompt.h"
#include "lookup.h"
#include "piping.h"

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
        commandsHere = separateCommands(input);
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
            // int check;
            if (checkpipes())
            {
                handlepipes();
            }
            else
            {
                check = lookup();
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