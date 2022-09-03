#ifndef COM_LS_H
#define COM_LS_H
#include "global.h"

int detailed_information(char file[], char fileName[])
{
    struct stat stats;
    if (stat(file, &stats) < 0)
    {
        return 0;
    }
    char permissions[11] = "----------\0";
    int check_perms[9] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};
    char perm_settings[3] = {'r', 'w', 'x'};
    if (S_ISDIR(stats.st_mode))
    {
        permissions[0] = 'd';
    }
    for (int i = 0; i < 9; i++)
    {
        if ((stats.st_mode & check_perms[i]))
        {
            permissions[i + 1] = perm_settings[i % 3];
        }
    }
    struct group *grp = getpwuid(stats.st_uid);
    struct passwd *pwd = getgrgid(stats.st_gid);
    time_t *t = malloc(1024);
    *t = stats.st_mtime;
    struct tm tm = *localtime(t);
    printf("%s", permissions);
    printf("%2ld ", stats.st_nlink);
    printf("%s ", pwd->pw_name);
    printf("%s ", grp->gr_name);
    printf("%9ld ", stats.st_size);
    printf("%s ", months[tm.tm_mon]);
    printf("%2d ", tm.tm_mday);
    printf("%02d:", tm.tm_hour);
    printf("%02d ", tm.tm_min);
    printf("%s\n", fileName);
    return 1;
}

int call_ls()
{
    int flags[2] = {0, 0};
    int A = 0;
    int L = 1;
    int count = 0;
    for (int a = 1; a < numargs; a++)
    {
        if (commands[a][0] != '-')
            continue;
        if (strlen(commands[a]) == 1)
            continue;
        for (int b = 1; b < strlen(commands[a]); b++)
            if (commands[a][b] == 'a')
                flags[A] = 1;
            else if (commands[a][b] == 'l')
                flags[L] = 1;
            else
            {
                printf("ls: invalid option -- '%c'\n", commands[a][b]);
                return 0;
            }
        count++;
    }
    int num_dir = numargs - 1 - count;
    int print_name = 0;
    if (num_dir > 1)
    {
        print_name = 1;
    }
    int shown = 1;
    if (num_dir == 0)
    {
        commands[numargs] = (char *)malloc(10 * sizeof(char));
        strcpy(commands[numargs], ".");
        numargs++;
    }
    int exitCode = 1;
    for (int a = 1; a < numargs; a++)
    {
        int x = strlen(commands[a]);
        if (commands[a][0] == '-')
            continue;
        if (commands[a][0] == '~')
        {
            if (strlen(commands[a]) == 1)
                strcpy(commands[a], shelldir);
            if (commands[a][1] == '/')
            {
                remove_suffix(commands[a], 1);
                string_prepend(commands[a], shelldir);
            }
        }
        DIR *dir = opendir(commands[a]);
        if (dir == NULL)
        {
            perror("ls");
            exitCode = 0;
            continue;
        }
        if (print_name)
        {
            printf("%s:\n", commands[a]);
        }
        // implements the -l flag
        if (flags[L])
        {
            struct stat stats;
            stat(commands[a], &stats);
            int total = 0;
            struct dirent *fileCount;
            fileCount = readdir(dir);
            while (fileCount != NULL)
            {
                char temp[1000];
                for (int i = 0; i < strlen(commands[a]); i++)
                {
                    temp[i] = commands[a][i];
                }
                temp[strlen(commands[a])] = '/';
                temp[strlen(commands[a]) + 1] = '\0';
                strcat(temp, fileCount->d_name);
                fileCount = readdir(dir);
                struct stat stats;
                stat(temp, &stats);
                total += stats.st_blocks;
            }
            printf("total %d\n", total / 2);
            rewinddir(dir);
        }
        struct dirent *fileHere;
        fileHere = readdir(dir);
        while (fileHere != NULL)
        {
            char temp[1000];
            for (int i = 0; i < strlen(commands[a]); i++)
            {
                temp[i] = commands[a][i];
            }
            temp[strlen(commands[a])] = '/';
            temp[strlen(commands[a]) + 1] = '\0';
            strcat(temp, fileHere->d_name);
            if (fileHere->d_name[0] != '.' || (fileHere->d_name[0] == '.' && flags[A]))
            {
                printf("\033[0;35m"); // prints in purple
                if (fileHere->d_type == DT_DIR)
                {
                    printf("\033[0;36m"); // prints in cyan
                }
                else
                {
                    struct stat stats;
                    stat(fileHere->d_name, &stats);
                    if ((stats.st_mode & S_IXUSR) || (stats.st_mode & S_IXOTH) || (stats.st_mode & S_IXGRP))
                    {
                        printf("\033[0;37m"); // prints in white
                    }
                }
                if (flags[L])
                {
                    int lscheck = detailed_information(temp, fileHere->d_name);
                }
                else
                {
                    printf("%s\n", fileHere->d_name);
                }
            }
            fileHere = readdir(dir);
        }
        if (num_dir > 1 && shown != num_dir)
        {
            printf("\n");
        }
        shown++;
    }
    return exitCode;
}
#endif