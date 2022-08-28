#include <stdio.h>

// Specification 1
void prompt()
{
}

int main()
{
    while (1)
    {
        prompt();
        char input[1000];
        scanf("%s ", input);
    }
    return 0;
}