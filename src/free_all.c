/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:38:20 by rburri            #+#    #+#             */
/*   Updated: 2022/02/25 10:50:39 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_data(t_data *data)
{	
	int	i;

	i = 0;
	if (data->cmd_args)
	{
		while (data->cmd_args[i])
			free(data->cmd_args[i++]);
		free(data->cmd_args);	
	}
	if (data->cmd)
		free(data->cmd);
	i = 0;
	if (data->pipe_fds)
	{
		while (data->pipe_fds[i])
			free(data->pipe_fds[i++]);
		free(data->pipe_fds);
	}
	i = 0;
	if (data->cmds)
	{
		while (data->cmds[i])
			free(data->cmds[i++]);
		free(data->cmds);
	}
	if (data->process_ids)
		free(data->process_ids);
	return (0);
}

int free_env(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd_paths)
	{
		while (data->cmd_paths[i])
			free(data->cmd_paths[i++]);
		free(data->cmd_paths);	
	}
	return (0);
}
