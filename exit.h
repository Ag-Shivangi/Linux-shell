#ifndef EXIT_FUNC
#define EXIT_FUNC
#include "global.h"
void exit_fun()
{
    int i, fileWriter = open("history.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    for (i = first_hist; (i % 20) != (size_hist + 19) % 20; i++)
    {
        write(fileWriter, history[i % 20], strlen(history[i]) * sizeof(char));
    }
    write(fileWriter, history[i % 20], strlen(history[i]) * sizeof(char));
    return;
}
#endif