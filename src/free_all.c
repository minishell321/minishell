/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:38:20 by rburri            #+#    #+#             */
/*   Updated: 2022/02/28 08:56:29 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_double_string_array(char **double_array)
{
	int	i;

	i = 0;
	while (double_array[i])
		free(double_array[i++]);
	free(double_array);
}

int	free_data(t_data *data)
{	
	int	i;

	i = 0;
	if (data->cmd_args)
		free_double_string_array(data->cmd_args);
	if (data->cmd)
		free(data->cmd);
	i = 0;
	if (data->pipe_fds)
	{
		while (i < data->num_of_pipe)
			free(data->pipe_fds[i++]);
		free(data->pipe_fds);
	}
	if (data->cmds)
		free_double_string_array(data->cmds);
	if (data->process_ids)
		free(data->process_ids);
	return (0);
}

int	free_env(t_data *data)
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
