#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>
#include <pwd.h>

char shelldir[1000];
const char *DELIMITER = " \t\r\n\a";
const int MAX_ARGUMENTS = 1024;
int numargs;
char **commands;
char lastpwd[1000];

#endif