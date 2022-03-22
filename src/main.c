/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:12 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 10:58:34 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

 static int	valid_command_buf(t_data *data, char **envp)
{
	add_history(data->command_buf);
	if (check_command(data->command_buf))
		return (1);
	if (check_is_heredoc(data->command_buf))
	{
		if (find_token(data, data->command_buf) || token_handler_heredoc(data))
			return (1);
		heredoc_handler(data, envp);
		return (1);
	}
	data->command_buf = find_dollars(data->command_buf, data);
	if (find_token(data, data->command_buf) || token_handler(data))
		return (1);
	if (check_exit(data))
		exit (data->exit_code);
	if (check_if_builtin(data))
	{
		if (exec_if_builtin(data))
			return (1);
		data->exit_code = 0;
		close_fds(data);
	}
	else if (exec_cmd(data, envp))
		return (1);
	return (0);
}

static int	start_prompt(t_data *data, char **envp)
{
	 while(1)
    {
		if (init_data(data))
			continue;
		data->command_buf = NULL;
		handle_sigs();
		data->command_buf = readline("minishell> ");
		if (data->command_buf == 0)
		{
			printf("exit\n");
			break;
		}
        if (data->command_buf && *data->command_buf)
		{
			if (valid_command_buf(data, envp))
				continue;
/*			data->command_buf = command_buf;
            add_history(command_buf);
			// if (check_exit(command_buf))
			// 	break;
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
				// printf("FINISHED TOKEN_HANDLER_HEREDOC\n");
				heredoc_handler(data, envp);
				continue;
			}
			command_buf = find_dollars(command_buf, data);
			if (find_token(data, command_buf))
				continue;
			print_token(data);
			if (token_handler(data))
				continue;
			check_exit(data);
			// check if free after break;
			if (check_if_builtin(data))
			{
				printf("IS BUILTIN\n");
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
				printf("IS EXEC_CMD\n");
				if (exec_cmd(data, envp))
					continue;
			}
*/		}
		// printf("############################create_cmd_table(heredoc or exec_cmd[0] = ***%s***\n", data->cmd_table[0][0]);
		
		free_data(data);
		if (data->command_buf)
			free(data->command_buf);
	}
	return (0);
}


int main(int argc, char **argv, char **envp)
{
	t_data data;

	if (argc != 1 || (!argv))
	{
		ft_putstr_fd("Error, no argument allowed\n", 2);
		return (1);
	}
	if (init_env(&data, envp))
	{
		printf("init env ERROR\n");
	}
	start_prompt(&data, envp);
	
	free_data(&data);
	if (data.command_buf)
		free(data.command_buf);
	if (data.environment)
		free_env(&data);
	return (0);
}
