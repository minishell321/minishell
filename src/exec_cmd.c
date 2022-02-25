/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 07:44:00 by rburri            #+#    #+#             */
/*   Updated: 2022/02/25 11:56:49 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// close fd_output, fd_input after dup2?
static int redirection_handler(t_data *data, int *i)
{
	if ((*i == 0) && (data->fd_input != 0))
	{
		if (dup2(data->fd_input, STDIN_FILENO) == -1)
			return (1);
		close(data->fd_input);
	}
	if ((*i == data->num_of_pipe) && (data->fd_output != 1))
	{
		if (dup2(data->fd_output, STDOUT_FILENO) == -1)
			return (1);
		close(data->fd_output);
	}
	return (0);
}

static int pipe_handler(t_data *data, int *i)
{
	int	j;

	j = 0;
	if (*i < data->num_of_pipe)
	{
		if (dup2(data->pipe_fds[*i][1], STDOUT_FILENO) == -1)
			return (1);
		printf("child: %d, dup2 STDOUT in pipe_fds[%d][1]\n", *i, *i);
		// close(data->pipe_fds[*i][1]);
	}
	if (*i > 0)
	{
		if (dup2(data->pipe_fds[(*(i) - 1)][0], STDIN_FILENO) == -1)
			return (1);
		printf("child: %d, dup2 STDIN in pipe_fds[%d][0]\n", *i, (*(i) - 1));
		// close(data->pipe_fds[*i - 1][0]);
	}
	while (j < data->num_of_pipe)
	{
		if (j != *i && j < data->num_of_pipe)
		{
			printf("child: %d, close: pipe_fds[%d][1]\n", *i, j);
			close(data->pipe_fds[j][1]);
		}
		if (j != *i -1)
		{
			printf("child: %d, close: pipe_fds[%d][0]\n", *i, j);
			close(data->pipe_fds[j][0]);
		}
		j++;
	}
	return (0);
}

int	exec_cmd(t_data *data, char **envp)
{
	int	i;

	i = 0;
	while (i < data->num_of_pipe + 1)
	{
		data->process_ids[i] = fork();
		if (data->process_ids[i] == -1)
			return (1);
			
		if (data->process_ids[i] == 0)
		{
			redirection_handler(data, &i);
			if (data->num_of_pipe > 0)
				pipe_handler(data, &i);
			
			data->cmd_args = ft_split(data->cmds[i], ' '); // change cmds with command_buf
			// data->cmd = get_cmd(data->cmd_paths, data->cmd_args[0]);
			if (get_cmd(data))
				return (1);
			execve(data->cmd, data->cmd_args, envp);
		}
		i++;
	}
	
	i = 0;
	while (i < data->num_of_pipe)
		waitpid(data->process_ids[i++], NULL, 0);
		//error handling
	return (0);
}