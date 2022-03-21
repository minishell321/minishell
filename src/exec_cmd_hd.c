/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_hd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 08:40:36 by rburri            #+#    #+#             */
/*   Updated: 2022/03/21 08:41:09 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	child_handler_hd(t_data *data, char **envp, int i)
{
	if (redir_handler(data, i))
		exit (1);
	if (pipe_handler(data, i))
	{
		perror("pipe_handler");
		exit (1);
	}
	if (get_cmd_hd(data, i))
		exit (1);
	if (execve(data->cmd, data->heredoc_other_cmds[i], envp))
	{
		perror("execve");
		exit (1);
	}
}

int	exec_cmd_hd(t_data *data, char **envp)
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
			child_handler_hd(data, envp, i);
		i++;
	}
	if (close_pipe_fds(data))
		return (1);
	if (wait_all_children(data))
		return (1);
	return (0);
}
