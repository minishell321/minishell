#include "../includes/minishell.h"


int main()
{
    char *command_buf;
    // int res;
    int res2;

    while(1)
    {
        command_buf = readline("testcli> ");
        res2 = strcmp(command_buf, "exit");
        if (ft_strlen(command_buf) > 0)
            add_history(command_buf);
        // res = ft_strcmp(command_buf, "exit");
        // printf("%d\n", res);
        printf("%d\n", res2);
        printf("%s\n", command_buf);
    }
}

//gcc readline.c -lreadline