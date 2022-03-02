/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:38:20 by rburri            #+#    #+#             */
/*   Updated: 2022/03/02 09:48:13 by rburri           ###   ########.fr       */
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
	// if (data->cmds)
	// 	free_double_string_array(data->cmds);
	if (data->process_ids)
		free(data->process_ids);
	if (data->token_stack)
				free_token_stack(data);
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

void	free_token_stack(t_data *data)
{
	t_token *tmp;
	int j = 0;
	while (data->token_stack)
	{
		tmp = data->token_stack;
		data->token_stack = data->token_stack->next;
		if (tmp->args)
		{
			t_token *tmp_arg;
			while (tmp->args)
			{
				tmp_arg = tmp->args;
				tmp->args = tmp->args->next;
				// printf("freeing ARG : %s from CDM : %s\n", tmp_arg->str, tmp->str);
				free(tmp_arg);
			}
		}
		// printf("freeing CDM : %s\n",tmp->str);
		free(tmp);
	}
}