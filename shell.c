#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "com_cd.h"
#include <unistd.h>
#include <string.h>

void initfun()
{
    size_t currdirname_size;
    char *currdirname = (char *)malloc(1000 * sizeof(char));
    char *result = getcwd(currdirname, currdirname_size);
    strcpy(shelldir, currdirname);
}
void currwd()
{
    size_t currdirname_size;
    char *currdirname = (char *)malloc(1000 * sizeof(char));
    char *result = getcwd(currdirname, currdirname_size);
    if (cdflag == 1)
    {
        printf("%s", currdirname);
        free(currdirname);
        return;
    }
    printf("%s", currdirname + strlen(shelldir));
}
char *readLine()
{
    char *ret = (char *)malloc(1000 * sizeof(char));
    size_t len = 1000;
    if (getline(&ret, &len, stdin) == -1)
    {
        printf("quit\n");
        _exit(2);
    }
    return ret;
}
// Specification 1
void prompt()
{
    size_t username_size, hostname_size;
    char *username = (char *)malloc(1000 * sizeof(char));
    char *hostname = (char *)malloc(1000 * sizeof(char));
    int res = getlogin_r(username, username_size);
    res = gethostname(hostname, hostname_size);
    printf("\033[0;32m");
    printf("<%s@%s", username, hostname);
    free(username);
    free(hostname);
    printf("\033[0;33m");
    printf(":~");
    currwd();
    printf("> ");
    printf("\033[0m");
}
char **separateInput(char *line)
{
    char **ret = (char **)malloc(MAX_ARGUMENTS * sizeof(char *));
    char *arg;
    int idx = 0;
    if (!ret)
    {
        perror("Memory allocation failure");
        exit(1);
    }
    arg = strtok(line, DELIMITER);
    while (arg != NULL)
    {
        ret[idx++] = arg;
        arg = strtok(NULL, DELIMITER);
    }
    ret[idx] = arg;
    numargs = idx;
    return ret;
}
int main()
{
    initfun();
    char input[1000];
    while (1)
    {
        prompt();
        strcpy(input, readLine());
        commands = separateInput(input);
        if (strcmp(commands[0], "exit") == 0)
            break;
        else if (strcmp(commands[0], "cd") == 0)
        {
            int check = call_cd();
        }
        free(commands);
    }
    return 0;
}