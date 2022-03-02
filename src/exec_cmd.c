/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 07:44:00 by rburri            #+#    #+#             */
/*   Updated: 2022/03/01 12:51:08 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	redirection_handler(t_data *data, int *i)
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

static int	pipe_handler(t_data *data, int *i)
{
	int	j;

	j = 0;
	if (*i < data->num_of_pipe)
	{
		if (dup2(data->pipe_fds[*i][1], STDOUT_FILENO) == -1)
			return (1);
		close(data->pipe_fds[*i][1]);
	}
	if (*i > 0)
	{
		if (dup2(data->pipe_fds[(*(i) - 1)][0], STDIN_FILENO) == -1)
			return (1);
		close(data->pipe_fds[*i - 1][0]);
	}
	while (j < data->num_of_pipe)
	{
		if (j != *i && j < data->num_of_pipe)
			close(data->pipe_fds[j][1]);
		if (j != *i - 1)
			close(data->pipe_fds[j][0]);
		j++;
	}
	return (0);
}

static int	close_pipe_fds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_pipe)
	{
		if (close(data->pipe_fds[i][0]))
		{
			ft_putstr_fd("Error, close pipe\n", 2);
			return (1);
		}
		if (close(data->pipe_fds[i][1]))
		{
			ft_putstr_fd("Error, close pipe\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	wait_all_children(t_data *data)
{
	int	i;
	int	res;

	i = 0;
	while (i <= data->num_of_pipe)
	{
		// printf("i = %d\nnum_of_pipe = %d\n", i , data->num_of_pipe);
		// printf("process_ids = %d\n", data->process_ids[i]);
		res = waitpid(data->process_ids[i], NULL, 0);
		if (res == -1)
		{
			ft_putstr_fd("Error, waitpid\n", 2);
			return (1);
		}
		i++;
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
			printf("%d\n", data->process_ids[i]);
			redirection_handler(data, &i);
			if (data->num_of_pipe > 0)
				pipe_handler(data, &i);
			if (get_cmd(data, i))
				return (1);
			printf("was here\n");
			if (execve(data->cmd, data->cmd_table[i], envp))
				printf("Error execve\n");
		}
		i++;
	}
	if (close_pipe_fds(data))
		return (1);
	if (wait_all_children(data))
		return (1);
	return (0);
}
