/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 07:44:00 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 07:24:43 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_handler(t_data *data, int i)
{
	if ((i == 0) && (data->fd_input != 0))
	{
		if (dup2(data->fd_input, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("redir_handler error\n", 2);
			return (1);
		}
		close(data->fd_input);
	}
	if ((i == data->num_of_pipe) && (data->fd_output != 1))
	{
		if (dup2(data->fd_output, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("redir_handler error\n", 2);
			return (1);
		}
		close(data->fd_output);
	}
	return (0);
}

static void	child_handler(t_data *data, char **envp, int i)
{
	if (redir_handler(data, i))
		exit (1);
	if (pipe_handler(data, i))
	{
		perror("pipe_handler");
		exit (1);
	}
	if (get_cmd(data, i))
		exit (127);
	if (execve(data->cmd, data->cmd_table[i], envp))
	{
		perror("execve");
		exit (1);
	}
}

int	wait_all_children(t_data *data)
{
	int	i;
	int	res;
	int	status;

	i = 0;
	res = 0;
	status = 0;
	while (i <= data->num_of_pipe)
	{
		res = waitpid(data->process_ids[i], &status, WUNTRACED);
		data->exit_code = WEXITSTATUS(status);
		while (res == -1)
		{
			res = waitpid(data->process_ids[i], &status, WUNTRACED);
			data->exit_code = WEXITSTATUS(status);
			// if (WIFSIGNALED(status))
			// {
			// 	if (WTERMSIG(status) == SIGINT)
			// 	{

			// 	}
			// 	if (WTERMSIG(status) == SIGQUIT)
			// 	{

			// 	}
			// }
		}
		i++;
	}
	return (0);
}

int	exec_cmd(t_data *data, char **envp)
{
	int	i;

	i = 0;
	handle_sigs_child();
	while (i < data->num_of_pipe + 1)
	{
		data->process_ids[i] = fork();
		if (data->process_ids[i] == -1)
			return (1);
		if (data->process_ids[i] == 0)
			child_handler(data, envp, i);
		i++;	
	}
	if (close_pipe_fds(data))
		return (1);
	if (wait_all_children(data))
		return (1);
	return (0);
}
