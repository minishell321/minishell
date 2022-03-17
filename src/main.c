/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:12 by rburri            #+#    #+#             */
/*   Updated: 2022/03/17 09:00:47 by rburri           ###   ########.fr       */
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
		data->command_buf = NULL;
		handle_sigs();
	//	printf("WHILE LOOP\n");
		// if (data->heredoc)
		// 	command_buf = readline("> ");
		// else
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
			//handle_sigs();
			if (init_data(data))
				continue;
			if (check_command(command_buf))
			 	continue;
			if (check_is_heredoc(command_buf))
			{
				if (find_token(data, command_buf))
					continue;
				printf("PRINT TOKEN STARTS\n");	
				print_token(data);
				printf("PRINT TOKEN ENDS\n");	
				if (token_handler_heredoc(data))
					continue;
				printf("FINISHED TOKEN_HANDLER_HEREDOC\n");
				heredoc_handler(data, envp);
				continue;
			}
			// if (data->heredoc)
			// {
			// //	printf("-IN HERE-\n");
			// 	heredoc_handler(data, envp);
			// 	continue;
			// }
			command_buf = find_dollars(command_buf, data);
			if (find_token(data, command_buf))
				continue;
			if (token_handler(data))
				continue;
			if (check_if_builtin(data))
			{
				printf("IS BUILTIN\n");
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
	// handle_sigs();
	start_prompt(command_buf, &data, envp);
	free_env(&data);
	return (0);
}
