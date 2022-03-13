/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 09:53:31 by rburri            #+#    #+#             */
/*   Updated: 2022/03/05 10:33:25 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	close_unused_pipe(t_data *data, int i)
{
	int	j;

	j = 0;
	while (j < data->num_of_pipe)
	{
		if (j != i && j < data->num_of_pipe)
		{
			if (close(data->pipe_fds[j][1]))
			{
				perror("close pipe");
				return (1);
			}
		}
		if (j != i - 1)
		{
			if (close(data->pipe_fds[j][0]))
			{
				perror("close pipe");
				return (1);
			}
		}
		j++;
	}
	return (0);
}

int	pipe_handler(t_data *data, int i)
{
	if (data->num_of_pipe > 0 && i < data->num_of_pipe)
	{
		if (dup2(data->pipe_fds[i][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		if (close(data->pipe_fds[i][1]))
		{
			perror("close pipe");
			return (1);
		}
	}
	if (data->num_of_pipe > 0 && i > 0)
	{
		if (dup2(data->pipe_fds[i - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		if (close(data->pipe_fds[i - 1][0]))
		{
			perror("close pipe");
			return (1);
		}
	}
	if (close_unused_pipe(data, i))
		return (1);
	return (0);
}

int	close_pipe_fds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_pipe)
	{
		if (close(data->pipe_fds[i][0]))
		{
			perror("close pipe");
			return (1);
		}
		if (close(data->pipe_fds[i][1]))
		{
			perror("close pipe");
			return (1);
		}
		i++;
	}
	return (0);
}
