#ifndef COM_JOBS
#define COM_JOBS

#include "global.h"

int call_jobs()
{
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
                printf("[%d] Stopped %s [%d]\n", i + 1, bgprocesses_name[i], bgprocesses_ID[i]);
            else
                printf("[%d] Running %s [%d]\n", i + 1, bgprocesses_name[i], bgprocesses_ID[i]);
        }
        else
            printf("[%d] Terminated %s [%d]\n", i + 1, bgprocesses_name[i], bgprocesses_ID[i]);
    }
    return 1;
}

#endif