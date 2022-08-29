#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
void currwd()
{
    size_t currdirname_size;
    char *currdirname = (char *)malloc(1000 * sizeof(char));
    char *currdir = (char *)malloc(1000 * sizeof(char));
    char *result = getcwd(currdirname, currdirname_size);
    int count = 0, index = 0;
    for (int i = 0; i < strlen(currdirname); i++)
    {
        if (currdirname[i] == '/')
        {
            count++;
        }
        if (count == 3)
        {
            index = i;
            break;
        }
    }
    for (int i = index; i < strlen(currdirname); i++)
    {
        currdir[i - index] = currdirname[i];
    }
    printf("\033[0;33m");
    printf(":~%s", currdir);
    free(currdirname);
    free(currdir);
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
    printf("%s@%s", username, hostname);
    free(username);
    free(hostname);
    printf("\033[0m");
    currwd();
    printf("\033[0m");
    printf("$ ");
}

int main()
{
    char input[1000];
    while (1)
    {
        prompt();
        // char *buffer;
        // size_t charac, buf_size = 1000;
        // buffer = (char *)malloc(sizeof(char) * buf_size);
        // charac = getline(&buffer, &buf_size, stdin);
        // strcpy(input, buffer);
        // free(buffer);
        scanf("%s", input);
        if (strcmp(input, "exit") == 0)
            break;
    }
    return 0;
}