/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 07:44:00 by rburri            #+#    #+#             */
/*   Updated: 2022/03/10 07:50:55 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	redirection_handler(t_data *data, int i)
{
	if ((i == 0) && (data->fd_input != 0))
	{
		if (dup2(data->fd_input, STDIN_FILENO) == -1)
			return (1);
		close(data->fd_input);
	}
	if ((i == data->num_of_pipe) && (data->fd_output != 1))
	{
		if (dup2(data->fd_output, STDOUT_FILENO) == -1)
			return (1);
		close(data->fd_output);
	}
	return (0);
}

static int	wait_all_children(t_data *data)
{
	int	i;
	int	res;

	i = 0;
	while (i <= (data->num_of_pipe))
	{
		res = waitpid(data->process_ids[i], NULL, 0);
		printf("waited for %d\n", res);
		if (res == -1)
		{
			ft_putstr_fd("Error, waitpid\n", 2);
			return (1);
		}
		i++;
	}
	printf("Waited for child....\n");
	return (0);
}

int	exec_cmd(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (i < data->num_of_pipe + 1)
	{
		data->process_ids[i] = fork();
		printf("BEFORE pid = %d\n", getpid());
		
		if (data->process_ids[i] == -1)
			return (1);
		if (data->process_ids[i] == 0)
		{
			redirection_handler(data, i);
			if (pipe_handler(data, i))
			{
				printf("PIPE ERR IN CHILD");
				exit (1);
			}
			if (get_cmd(data, i))
			{
				printf("error get_cmd");
				exit (1);
			}
			printf("pid = %d\n", getpid());
			if (execve(data->cmd, data->cmd_table[i], envp))
			{
				ft_putstr_fd("Error execve\n", 2);
				// exit (1);
			}
		}
		i++;	
	}
	printf("Goes here, main\n");
	
	if (close_pipe_fds(data))
		return (1);
	if (wait_all_children(data))
		return (1);
	return (0);
}
