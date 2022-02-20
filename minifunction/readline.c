#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

char *command_buf;

int main()
{
    while(1)
    {
        command_buf = readline("testcli> ");
        if (strlen(command_buf) > 0)
            add_history(command_buf);
        else if (!strcmp(command_buf, "exit"))
            break;
    }
}

#gcc readline.c -lreadline