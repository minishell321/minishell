/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:12 by rburri            #+#    #+#             */
/*   Updated: 2022/03/10 10:36:43 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start_prompt(char *command_buf, t_data *data, char **envp)
{
	int pid;

	 while(1)
    {
        command_buf = readline("testcli> ");
		if (command_buf == 0)
		{
			printf("exit\n");
			break;
		}
        if (command_buf && *command_buf)
		{
            add_history(command_buf);
			if ((ft_strncmp(command_buf, "exit", 4)) == 0)
				break;
			handle_sigs();
			init_data(data, envp);
			if (check_command(command_buf))
			 	continue;
			// replace var env
			if (find_token(data, command_buf))
			{
				printf("error find token\n");
				continue;
			}
			if (token_handler(data))
				continue;
			if (check_if_builtin(data))
			{
				printf("IS BUILTIN\n");
				// TODO, check error for builtins, ex if have a pipe.
				if (exec_if_builtin(data))
					continue;
				close_fds(data);
			}
			else
			{
				printf("IS EXEC_CMD\n");
				if (exec_cmd(data, envp))
					continue;
			}
			if (data)
				free_data(data);
		}
		if (command_buf)
			free(command_buf);
	}
	return (0);
}


int main(int argc, char **argv, char **envp)
{
    char *command_buf;
	t_data data;
	int pid;
	
	command_buf = NULL;
	if (init_env(&data, envp))
	{
		printf("init env ERROR\n");
	}
	// handle_sigs();
	start_prompt(command_buf, &data, envp);
	free_env(&data);
	return (0);
}
