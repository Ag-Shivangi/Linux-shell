#ifndef COM_HIS_H
#define COM_HIS_H
#include "global.h"
int call_history()
{
    // printf("%d %d\n", first_hist, size_hist);
    if (size_hist == 0)
    {
        return 1;
    }
    if (size_hist < 10)
    {
        for (int i = first_hist; i < size_hist; i++)
        {
            printf("%s", history[(i % 20)]);
        }
        return 1;
    }
    for (int i = (size_hist + 10) % 20; (i % 20) != ((size_hist + 19) % 20); i++)
    {
        printf("%s", history[(i % 20)]);
    }
    printf("%s", history[(size_hist + 19) % 20]);
    return 1;
}
#endif