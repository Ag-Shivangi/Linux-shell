#ifndef COM_JOBS
#define COM_JOBS

#include "global.h"

int call_jobs()
{
    int flagR = 1;
    int flagS = 1;
    if (numargs > 2)
    {
        printf("%s: Invalid number of arguments\n", commands[0]);
        return 0;
    }
    if (numargs == 2)
    {
        if (commands[1][0] != '-' || strlen(commands[1]) != 2)
        {
            printf("%s: Invalid argument %s\n", commands[0], commands[1]);
            return 0;
        }
        if (commands[1][1] == 'r')
            flagS = 0;
        else if (commands[1][1] == 's')
            flagR = 0;
        else
        {
            printf("%s: Invalid argument %s\n", commands[0], commands[1]);
            return 0;
        }
    }
    for (int i = 0; i < bgcommands_num; i++)
    {
        if (getpgid(bgprocesses_ID[i]) >= 0)
        {
            // /proc/<num>/stat
            char processFile[1000] = {"/stat"};
            char line[1000];
            char *pidinchar = my_itoa(bgprocesses_ID[i]);
            string_prepend(processFile, pidinchar);
            string_prepend(processFile, "/proc/");
            FILE *reader = fopen(processFile, "r");
            fgets(line, 1000, reader);
            int cnt = 0, idx;
            for (idx = 0; idx < strlen(line); idx++)
            {
                if (line[idx] == ' ')
                    cnt++;
                if (cnt >= 2)
                    break;
            }
            idx++;
            char ret = line[idx];
            if (ret == 'T')
            {
                if (flagS)
                    printf("[%d] Stopped %s [%d]\n", i + 1, bgprocesses_name[i], bgprocesses_ID[i]);
            }
            else
            {
                if (flagR)
                    printf("[%d] Running %s [%d]\n", i + 1, bgprocesses_name[i], bgprocesses_ID[i]);
            }
        }
    }
    return 1;
}

#endif