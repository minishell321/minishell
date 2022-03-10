/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:38:20 by rburri            #+#    #+#             */
/*   Updated: 2022/03/10 07:16:07 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_cmd_table(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->cmd_table[i])
	{
		j = 0;
		while (data->cmd_table[i][j])
		{
			// printf("free : cmd_table[%d][%d] : %s\n", i, j, data->cmd_table[i][j]);
			free(data->cmd_table[i][j++]);
		}
		i++;
	}
	free(data->cmd_table);
}

int	free_data(t_data *data)
{	
	int	i;

	if (data->cmd)
		free(data->cmd);
	i = 0;
	if (data->pipe_fds)
	{
		while (i < data->num_of_pipe)
			free(data->pipe_fds[i++]);
		free(data->pipe_fds);
	}
	if (data->cmd_table)
		free_cmd_table(data);
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

void	free_token_stack(t_data *data)
{
	t_token	*tmp;
	t_token	*tmp_arg;
	int		j;

	j = 0;
	while (data->token_stack)
	{
		tmp = data->token_stack;
		data->token_stack = data->token_stack->next;
		if (tmp->args)
		{
			while (tmp->args)
			{
				tmp_arg = tmp->args;
				tmp->args = tmp->args->next;
				free(tmp_arg);
			}
		}
		free(tmp);
	}
}

void	close_fds(t_data *data)
{
	if (data->fd_input != 0)
		close(data->fd_input);
	if (data->fd_output != 1)
		close(data->fd_output);
}
