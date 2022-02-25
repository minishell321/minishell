/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:13:13 by vbotev            #+#    #+#             */
/*   Updated: 2022/02/25 11:57:51 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create the array of fds for each pipe
static int create_2d(t_data  *data)
{	
	int	i;
	int **pipe_fds;
	
	i = 0;
	if (data->num_of_pipe == 0)
		return (0);
	pipe_fds = (int **)malloc(data->num_of_pipe * sizeof(int *));
	if (pipe_fds == NULL)
	{
		ft_putendl_fd("Error malloc pipe_fds", 2);
		return (1);
	}
	while (i < data->num_of_pipe)
	{
		pipe_fds[i] = malloc(2 * sizeof(int));
		if (pipe_fds[i] == NULL)
		{
			ft_putendl_fd("Error malloc pipe_fds", 2);
			return (1);
		}
		if (pipe(pipe_fds[i]) == -1)
		{
			ft_putendl_fd("error create pipe", 2);
			return (1);
		}
		// printf("pipe:%i, pipe_fd0: %d, pipe_fd1: %d\n", i, pipe_fds[i][0], pipe_fds[i][1]);
		i++;
	}
	data->pipe_fds = pipe_fds;
	return (0);
}

// Create int array to store processes ids
static int create_pids_arr(t_data *data)
{
	data->process_ids = (int *)malloc((data->num_of_pipe + 1) * sizeof(int));
	if (data->process_ids == NULL)
		return (1);
	return (0);
}
// TEST CMDS
static char **create_cmds_test(char **cmds)
{
	int i = 0;
	cmds = (char **)malloc(3 * sizeof(char *));
	cmds[0] = ft_strdup("ls -la");
	cmds[1] = ft_strdup("cat -e");
	cmds[2] = ft_strdup("cat -e");
	cmds[3] = NULL;
	return (cmds);
}

// Initialise the struct t_data, setting variables that are not yet assigned to 0 (or default)
int	init_data(t_data *data, char **envp)
{
	data->cmd_args = 0;
	data->cmd = 0;
	data->fd_input = 0;
	data->fd_output = 1;
	data->num_of_pipe = 2;
	data->pipe_fds = 0; 
	if (create_2d(data))
		return (1);
	data->process_ids = 0;
	if (create_pids_arr(data))
		return(1);
	data->cmds = create_cmds_test(data->cmds);
	return (0);
}

int init_env(t_data *data, char **envp)
{
	data->env_paths = 0;
	if (find_path(data, envp))
		return (1);
	data->cmd_paths = ft_split(data->env_paths, ':');
	if (data->cmd_paths == NULL)
	{
		ft_putendl_fd("Error, split env_paths", 2);
		return (1);
	}	
	return (0);
}