/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:13:13 by vbotev            #+#    #+#             */
/*   Updated: 2022/02/23 10:01:35 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create the array of fds for each pipe
static int create_2d(int num_of_pipe, int **pipe_fds)
{	
	int	i;
	
	i = 0;
	if (num_of_pipe == 0)
		return (0);
	pipe_fds = malloc(num_of_pipe * sizeof(int *));
	if (pipe_fds == NULL)
		return (1);
	while (i < num_of_pipe)
	{
		pipe_fds[i] = malloc(2 * sizeof(int));
		{
			//error treatment
		}
		
		if (pipe(pipe_fds[i]) == -1)
		{
			//error treatment
			//!!close all pipes created
			return (1);
		}
			
	}
	return (0);
}

// Create int array to store processes ids
static int create_pids_arr(int num_of_pipe, int *process_ids)
{
	process_ids = (int *)malloc((num_of_pipe + 1) * sizeof(int));
	if (process_ids == NULL)
		return (1);
	return (0);
}

// Initialise the struct t_data, setting variables that are not yet assigned to 0 (or default)
int	init_data(t_data *data, char **envp)
{
	data->env_paths = find_path(envp);
	data->cmd_paths = ft_split(data->env_paths, ':');
	data->cmd_args = 0;
	data->cmd = 0;
	data->fd_input = 0;
	data->fd_output = 1;
	data->num_of_pipe = 0;
	data->pipe_fds = create_2d(data->num_of_pipe, &data->pipe_fds);
	data->process_ids = create_pids_arr(data->num_of_pipe, &data->process_ids);
	
	return (0);
}
