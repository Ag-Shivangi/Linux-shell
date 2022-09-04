# Ssh
To compile the shell run 
```bash 
make
```
To run the shell use the command
```bash
./a.out
```

### Assumptions:
- The maximum number of arguments- 1000
- The maximum length of input- 1000
- Maximum number of background process- 1000
- If only 1 non-flag argument is provided for discover, it is considered to be the path
- If no flags are provided for discover, both flags are assumed.

### Directory Format
Input is handled in "shell.c" which calls functions to execute the commands accordingly.
Each command and type of process is implemented in a separate header file. 
All standard libraries used have been included in "global.h". The global variables and repeated generic functions are also in "global.h".  
