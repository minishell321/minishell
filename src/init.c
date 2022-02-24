/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:13:13 by vbotev            #+#    #+#             */
/*   Updated: 2022/02/24 10:21:24 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create the array of fds for each pipe
static int **create_2d(int num_of_pipe)
{	
	int	i;
	int **pipe_fds;
	
	i = 0;
	if (num_of_pipe == 0)
		return (0);
	pipe_fds = (int **)malloc(num_of_pipe * sizeof(int *));
	if (pipe_fds == NULL)
		return (NULL);
	while (i < num_of_pipe)
	{
		pipe_fds[i] = malloc(2 * sizeof(int));
		if (pipe_fds[i] == NULL)
		{
			printf("error malloc pipe\n");
			return (NULL);
		}
		
		if (pipe(pipe_fds[i]) == -1)
		{
			printf("error create pipe\n");
		}
		printf("pipe:%i, pipe_fd0: %d, pipe_fd1: %d\n", i, pipe_fds[i][0], pipe_fds[i][1]);
		i++;
	}
	return (pipe_fds);
}

// Create int array to store processes ids
static int *create_pids_arr(int num_of_pipe)
{
	int *process_ids;
	process_ids = (int *)malloc((num_of_pipe + 1) * sizeof(int));
	if (process_ids == NULL)
		return (NULL);
	return (process_ids);
}
// TEST CMDS
static char **create_cmds_test(char **cmds)
{
	int i = 0;
	cmds = (char **)malloc(2 * sizeof(char *));
	cmds[0] = ft_strdup("pwd");
	cmds[1] = ft_strdup("cat -e");
	return (cmds);
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
	data->num_of_pipe = 2;
	data->pipe_fds = create_2d(data->num_of_pipe);
	data->process_ids = create_pids_arr(data->num_of_pipe);
	data->cmds = create_cmds_test(data->cmds);
	
	return (0);
}
