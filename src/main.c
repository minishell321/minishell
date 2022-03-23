/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:12 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 11:57:22 by vbotev           ###   ########.fr       */
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
	while (1)
	{
		if (init_data(data))
			continue ;
		data->command_buf = NULL;
		handle_sigs();
		data->command_buf = readline("minishell> ");
		if (data->command_buf == 0)
		{
			printf("exit\n");
			break ;
		}
		if (data->command_buf && *data->command_buf)
		{
			if (valid_command_buf(data, envp))
				continue ;
		}
		free_data(data);
		if (data->command_buf)
			free(data->command_buf);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

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
