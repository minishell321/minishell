/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:13:13 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/03 09:58:46 by rburri           ###   ########.fr       */
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
int	init_data(t_data *data, char **envp)
{
	data->cmd = 0;
	data->fd_input = 0;
	data->fd_output = 1;
	data->num_of_pipe = 0;
	data->pipe_fds = 0;
	data->process_ids = 0;
	data->token_stack = 0;
	data->cmd_table = 0;
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
	data->cmd_table = 0;
	return (0);
}

// TEST CMDS
// static char	**create_cmds_test(char **cmds)
// {
// 	int	i;

// 	i = 0;
// 	cmds = (char **)malloc(5 * sizeof(char *));
// 	cmds[0] = ft_strdup("ls -la");
// 	cmds[1] = ft_strdup("cat -e");
// 	cmds[2] = ft_strdup("cat -e");
// 	cmds[3] = ft_strdup("grep d");
// 	cmds[5] = NULL;
// 	return (cmds);
// }

// void print_token_stack(t_data *data)
// {
// 	t_token *tmp;
// 	tmp = data->token_stack;
// 	int j = 0;
// 	while (tmp)
// 	{
// 		printf("cmd[%d]: %s\n", j, tmp->str);
// 		if (tmp->args)
// 		{
// 			t_token *tmp_arg;
// 			tmp_arg = tmp->args;
// 			int i = 0;
// 			while (tmp_arg)
// 			{
// 				printf("arg[%d]: %s\n", i, tmp_arg->str);
// 				tmp_arg = tmp_arg->next;
// 				i++;
// 			}
// 		}
// 		tmp = tmp->next;
// 		j++;
// 	}
// }