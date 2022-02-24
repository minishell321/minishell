/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 07:44:00 by rburri            #+#    #+#             */
/*   Updated: 2022/02/24 08:16:37 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int redirection_handler(t_data *data, int *i)
{
	if ((*i == 0) && (data->fd_input != 0))
	{
		if (dup2(data->fd_output, STDIN_FILENO) == -1)
			return (1);
	}
	if ((*i == data->num_of_pipe) && (data->fd_input != 1))
	{
		if (dup2(data->fd_output, STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}

static int pipe_handler(t_data *data, int *i)
{
	int	j;

	j = 0;
	while (j < data->num_of_pipe + 1)
	{
		if (j != *i && j < data->num_of_pipe)
			close(data->pipe_fds[j][1]);
		if (j != *i -1)
			close(data->pipe_fds[j][0]);
		j++;
	}
	if (*i < data->num_of_pipe)
		if (dup2(data->pipe_fds[*i][1], STDOUT_FILENO) == -1)
			return (1);
	if (*i > 0)
		if (dup2(data->pipe_fds[*i - 1][0], STDIN_FILENO) == -1)
				return (1);
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
			
		if (data->process_ids[i] = 0)
		{
			redirection_handler(data, &i);
			if (data->num_of_pipe > 0)
				pipe_handler(data, &i);
			//exec here			
			return (0);
		}
		i++;
	}
	
	i = 0;
	while (i < data->num_of_pipe + 1)
		waitpid(data->process_ids[i++], NULL, 0);
		//error handling
	return (0);
}