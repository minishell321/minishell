/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:13:13 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/17 15:20:17 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create the array of fds for each pipe
int	init_pipe_fds(t_data *data)
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
int	init_pids_arr(t_data *data)
{
	data->process_ids = (int *)malloc((data->num_of_pipe + 1) * sizeof(int));
	if (data->process_ids == NULL)
		return (1);
	return (0);
}

// Initialise the struct t_data, setting variables
//that are not yet assigned to 0 (or default)
int	init_data(t_data *data)
{
// 	if (data->heredoc_delim)
// 	{
// //		printf("The flag was set to 1\n");
// 		data->heredoc = 1;
// 	}
// 	else
// 	{
// //		printf("The flag is at default (NULL)\n");
// 		data->heredoc = 0;
// 	}
	data->heredoc_ign_tab = 0;
	data->cmd = 0;
	data->fd_input = 0;
	data->fd_output = 1;
	data->num_of_pipe = 0;
	data->pipe_fds = 0;
	data->process_ids = 0;
	data->token_stack = 0;
	data->cmd_table = 0;
	if (find_path(data))
		return (1);
	data->cmd_paths = ft_split(data->env_paths, ':');
	if (data->cmd_paths == NULL)
	{
		ft_putstr_fd("Error, split env_paths\n", 2);
		return (1);
	}
	return (0);
}

int	init_env(t_data *data, char **envp)
{
	data->environment = 0;
	if (local_env(data, envp))
		return (1);
	data->env_paths = 0;
	data->cmd_table = 0;
	data->exit_code = 0;
	data->heredoc_delim = 0;
	data->heredoc_str = 0;
	data->heredoc_other_cmds = 0;
	return (0);
}
