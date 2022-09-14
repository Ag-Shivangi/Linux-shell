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
- Colour has not been implemented for discover (no such requirement mentioned)
- Hidden directories will be printed in discover (nothing was mentioned in the pdf)
- The command "exit" ends the session. 
- The history for a given session updates iff exit is called; otherwise it is reset to the state before the session.
- The exit command is also added to the history.

### Directory Format
"shell.c" calls functions to execute the commands entered using a lookup table.
Each command and type of process is implemented in a separate header file. 
All standard libraries used have been included in "global.h". The global variables and repeated generic functions are also in "global.h".  
Input, Prompt and Signals are handled in separate header files- "inputmanipulation.h" , "prompt.h" and "signalhandle.h".
A Makefile is included to compile the shell.
