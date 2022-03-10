/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 07:44:00 by rburri            #+#    #+#             */
/*   Updated: 2022/03/10 07:07:39 by rburri           ###   ########.fr       */
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
	int status;

	i = 0;
	res = 0;
	status = 0;
	while (i <= data->num_of_pipe)
	{
	//	res = waitpid(data->process_ids[i], NULL, 0);
		res = waitpid(data->process_ids[i], &status, WUNTRACED);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
			{
				ft_putstr_fd("SIGINT terminated child\n", 2);
				rl_replace_line("", 0);
		//		rl_on_new_line();
		//		rl_redisplay();
			}
			else if (WTERMSIG(status) == SIGQUIT)
			{
				ft_putstr_fd("^\\Quit: 3\n", 2);
			}
		}
		while (!WIFSIGNALED(status) && !WIFEXITED(status))
		{
			printf("Here\n");
			res = waitpid(data->process_ids[i], &status, WUNTRACED);
		}
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
			redirection_handler(data, i);
		//	handle_sigs_child();
			if (pipe_handler(data, i))
				return(1);
			if (get_cmd(data, i))
			return (1);
			if (execve(data->cmd, data->cmd_table[i], envp))
			{
			//	ft_putstr_fd("Error execve\n", 2);
				perror("Error execve");
				return (1);
			}
		}
		i++;
	}
	if (close_pipe_fds(data))
		return (1);
	if (wait_all_children(data))
		return (1);
	return (0);
}
