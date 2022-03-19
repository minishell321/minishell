/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:12 by rburri            #+#    #+#             */
/*   Updated: 2022/03/19 16:04:19 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int check_exit(char *command_buf)
{
	char	*tmp;
	int		i;

	tmp = ft_strtrim(command_buf, " ");
	i = ft_strlen(tmp);	
	if ((i == 4 && !ft_strncmp(tmp, "exit", 4)) || !ft_strncmp(tmp, "exit ", 5))
	{
		printf("exit\n");
		free(tmp);	
		return (1);
	}
	free(tmp);	
	return (0);
}

int	start_prompt(char *command_buf, t_data *data, char **envp)
{
	 while(1)
    {
		if (init_data(data))
			continue;
		data->command_buf = NULL;
		handle_sigs();
		command_buf = readline("testcli> ");
		if (command_buf == 0)
		{
			printf("exit\n");
			break;
		}
        if (command_buf && *command_buf)
		{
			data->command_buf = command_buf;
            add_history(command_buf);
			if (check_exit(command_buf))
				break;
			// if (init_data(data))
			// 	continue;
			if (check_command(command_buf))
			 	continue;
			if (check_is_heredoc(command_buf))
			{
				if (find_token(data, command_buf))
					continue;
				if (token_handler_heredoc(data))
					continue;
				printf("FINISHED TOKEN_HANDLER_HEREDOC\n");
				heredoc_handler(data, envp);
				continue;
			}
			command_buf = find_dollars(command_buf, data);
			if (find_token(data, command_buf))
				continue;
			print_token(data);
			if (token_handler(data))
				continue;
			if (check_if_builtin(data))
			{
				// printf("IS BUILTIN\n");
				if (exec_if_builtin(data))
				{
					printf("Problem BUILTINS\n");
					continue;
				}
				data->exit_code = 0;		
				close_fds(data);
			}
			else
			{
				// printf("IS EXEC_CMD\n");
				if (exec_cmd(data, envp))
					continue;
			}
		}
		printf("############################create_cmd_table(heredoc or exec_cmd[0] = ***%s***\n", data->cmd_table[0][0]);
		if (data)
			free_data(data);
		if (command_buf)
			free(command_buf);
	}
	return (0);
}


int main(int argc, char **argv, char **envp)
{
    char *command_buf;
	t_data data;
	
	command_buf = NULL;
	if (argc != 1 || (!argv))
	{
		ft_putstr_fd("Error, no argument allowed\n", 2);
		return (1);
	}
	if (init_env(&data, envp))
	{
		printf("init env ERROR\n");
	}
	start_prompt(command_buf, &data, envp);
	return (0);
}
