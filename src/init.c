/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:13:13 by vbotev            #+#    #+#             */
/*   Updated: 2022/02/26 15:43:20 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create the array of fds for each pipe
static int	create_2d(t_data *data)
{	
	int	i;

	if (data->num_of_pipe == 0)
		return (0);
	data->pipe_fds = (int **)malloc(data->num_of_pipe * sizeof(int *));
	if (data->pipe_fds == NULL)
		return (1);
	i = 0;
	while (i < data->num_of_pipe)
	{
		data->pipe_fds[i] = (int *)malloc(2 * sizeof(int));
		if (data->pipe_fds[i] == NULL)
			return (1);
		if (pipe(data->pipe_fds[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

// Create int array to store processes ids
static int	create_pids_arr(t_data *data)
{
	data->process_ids = (int *)malloc((data->num_of_pipe + 1) * sizeof(int));
	if (data->process_ids == NULL)
		return (1);
	return (0);
}

// TEST CMDS
static char	**create_cmds_test(char **cmds)
{
	int	i;

	i = 0;
	cmds = (char **)malloc(5 * sizeof(char *));
	cmds[0] = ft_strdup("ls -la");
	cmds[1] = ft_strdup("cat -e");
	cmds[2] = ft_strdup("cat -e");
	cmds[3] = ft_strdup("grep d");
	cmds[4] = NULL;
	return (cmds);
}

// Initialise the struct t_data, setting variables that are not yet assigned to 0 (or default)
int	init_data(t_data *data, char **envp)
{
	data->cmd_args = 0;
	data->cmd = 0;
	data->fd_input = 0;
	data->fd_output = 1;
	data->num_of_pipe = 3;
	data->pipe_fds = 0;
	if (create_2d(data))
	{
		ft_putstr_fd("Error, create pipe_fds\n", 2);
		return (1);
	}
	data->process_ids = 0;
	if (create_pids_arr(data))
		return (1);
	data->cmds = create_cmds_test(data->cmds);
	return (0);
}

int	init_env(t_data *data, char **envp)
{
	data->env_paths = 0;
	if (find_path(data, envp))
		return (1);
	data->cmd_paths = ft_split(data->env_paths, ':');
	if (data->cmd_paths == NULL)
	{
		ft_putstr_fd("Error, split env_paths\n", 2);
		return (1);
	}	
	return (0);
}
