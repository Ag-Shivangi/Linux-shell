#ifndef INIT_FUNC
#define INIT_FUNC
#include "global.h"
long long int getSize(const char *path)
{
    struct stat *stats;
    stats = malloc(sizeof(struct stat));
    stat(path, stats);
    return stats->st_size;
}
void initfun()
{
    struct utsname xname;
    uname(&xname);
    char currdirname[1000];
    char *result = getcwd(currdirname, sizeof(currdirname));
    strcpy(shelldir, currdirname);
    Shell_Id = (int)getpid();
    curFgProc = (int)getpid();
    for (int i = 0; i < 20; i++)
    {
        history[i] = (char *)malloc(sizeof(char) * 1000);
    }
    first_hist = 0;
    size_hist = 0;
    char ifile[20];
    strcpy(ifile, "history.txt");
    int fileReader = open(ifile, O_RDONLY);
    if (fileReader == -1)
    {
        return;
    }
    int length = getSize(ifile);
    char t[2];
    for (int i = 0; i < length; i++)
    {
        read(fileReader, t, sizeof(char));
        strcat(history[size_hist], t);
        if (t[0] == '\n')
        {
            size_hist++;
            // printf("%d\n", size_hist);
        }
    }
}
#endif