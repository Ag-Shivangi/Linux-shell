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
    printf("%s", permissions);
    printf("%2ld ", stats.st_nlink);
    struct passwd *pwd = getgrgid(stats.st_gid);
    printf("%s ", pwd->pw_name);
    struct group *grp = getpwuid(stats.st_uid);
    printf("%s ", grp->gr_name);
    printf("%9ld ", stats.st_size);
    struct tm tm = *localtime(&stats.st_mtime);
    printf("%s %2d %02d:%02d ", months[tm.tm_mon], tm.tm_mday, tm.tm_hour, tm.tm_min);
    printf("%s\n", fileName);
    return 1;
}

int call_ls()
{
    int flags[2] = {0, 0}, A = 0, L = 1, count = 0;
    for (int i = 1; i < numargs; i++)
    {
        if (commands[i][0] != '-')
            continue;
        if (strlen(commands[i]) == 1)
            continue;
        for (int j = 1; j < strlen(commands[i]); j++)
            if (commands[i][j] == 'a')
                flags[A] = 1;
            else if (commands[i][j] == 'l')
                flags[L] = 1;
            else
            {
                printf("ls: invalid option -- '%c'\n", commands[i][j]);
                return 0;
            }
        count++;
    }
    int num_dir = numargs - 1 - count, print_name = 0;
    if (num_dir > 1)
    {
        print_name = 1;
    }
    if (num_dir == 0)
    {
        commands[numargs] = (char *)malloc(100);
        strcpy(commands[numargs++], ".\0");
    }
    int correctDirs = num_dir;
    for (int a = 1; a < numargs; a++)
    {
        if (commands[a][0] == '-')
        {
            correctDirs--;
            continue;
        }
        if (commands[a][0] == '~')
        {
            if (strlen(commands[a]) == 1)
            {
                strcpy(commands[a], shelldir);
            }
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
            correctDirs--;
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
            struct dirent *fileCount = readdir(dir);
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
                if (stat(temp, &stats) < 0)
                {
                    perror("ls");
                    continue;
                }
                total += stats.st_blocks;
            }
            printf("total %d\n", total / 2);
        }
        rewinddir(dir);
        struct dirent *fileHere = readdir(dir);
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
                    if (stat(temp, &stats) < 0)
                    {
                        perror("ls");
                        fileHere = readdir(dir);
                        continue;
                    }
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
        if (fileHere != NULL)
        {
            printf("\n");
        }
    }
    return (correctDirs == num_dir);
}
#endif