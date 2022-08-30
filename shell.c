
#include "global.h"
#include "com_cd.h"
#include "com_echo.h"
#include "com_pwd.h"
void initfun()
{
    struct utsname xname;
    uname(&xname);
    char currdirname[1000];
    char *result = getcwd(currdirname, sizeof(currdirname));
    strcpy(shelldir, currdirname);
}
void currwd()
{
    struct utsname xname;
    uname(&xname);
    char currdirname[1000];
    char *result = getcwd(currdirname, sizeof(currdirname));

    int cflag = 0;
    if (strlen(currdirname) < strlen(shelldir))
        cflag = 1;
    else
    {
        for (int i = 0; i < strlen(shelldir); i++)
            if (shelldir[i] != currdirname[i])
            {
                cflag = 1;
                break;
            }
    }
    if (cflag == 1)
        printf("%s", currdirname);
    else
    {
        printf("~");
        for (int i = strlen(shelldir); i < strlen(currdirname); i++)
            printf("%c", currdirname[i]);
    }
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
    struct utsname xname;
    uname(&xname);
    struct passwd *p = getpwuid(getuid());
    size_t username_size, hostname_size;
    char *username = p->pw_name;
    char *hostname = xname.nodename;
    printf("\033[0;32m");
    printf("<%s@%s", username, hostname);
    printf("\033[0;33m");
    printf(":");
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

char **separateCommands(char *line)
{
    char **ret = (char **)malloc(MAX_ARGUMENTS * sizeof(char *));
    char *arg;
    const char x[] = ";";
    int idx = 0;
    if (!ret)
    {
        perror("Memory allocation failure");
        exit(1);
    }
    arg = strtok(line, x);
    while (arg != NULL)
    {
        ret[idx] = arg;
        idx++;
        arg = strtok(NULL, x);
    }
    ret[idx] = arg;
    numcommands = idx;
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
        char **commandsHere = separateCommands(input);
        for (int i = 0; i < numcommands; i++)
        {
            commands = separateInput(commandsHere[i]);
            if (strcmp(commands[numargs - 1], "&") == 0)
            {
                curCommandBg = 1;
                numargs--;
            }
            else
            {
                curCommandBg = 0;
            }
            int check;
            if (strcmp(commands[0], "exit") == 0)
                break;
            else if (strcmp(commands[0], "cd") == 0)
            {
                check = call_cd();
            }
            else if (strcmp(commands[0], "pwd") == 0)
            {
                check = call_pwd();
            }
            else if (strcmp(commands[0], "echo") == 0)
            {
                check = call_echo();
            }
            // for (int i = 0; i < numargs; i++)
            // {
            //     free(commands[i]);
            // }
            free(commands);
        }
        free(commandsHere);
    }
    return 0;
}