/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:38:20 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 11:47:06 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_heredoc_other_cmds(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->heredoc_other_cmds[i])
	{
		j = 0;
		while (data->heredoc_other_cmds[i][j])
			free(data->heredoc_other_cmds[i][j++]);
		free(data->heredoc_other_cmds[i]);
		i++;
	}
	free(data->heredoc_other_cmds);
}

static void	free_cmd_table(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->cmd_table[i] != NULL)
	{
		j = 0;
		while (data->cmd_table[i][j] != NULL)
		{
			free(data->cmd_table[i][j]);
			j++;
		}
		free(data->cmd_table[i]);
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
	if (data->heredoc_other_cmds)
		free_heredoc_other_cmds(data);
	if (data->process_ids)
		free(data->process_ids);
	if (data->cmd_paths)
	{
		while (data->cmd_paths[i])
			free(data->cmd_paths[i++]);
		free(data->cmd_paths);
	}
	return (0);
}

int	free_env(t_data *data)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = data->environment;
	while (tmp != NULL)
	{
		if (tmp->variable)
			free(tmp->variable);
		if (tmp->value)
			free(tmp->value);
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	return (0);
}

void	free_heredoc(t_data *data)
{
	if (data->heredoc_str)
		free (data->heredoc_str);
	data->heredoc_str = 0;
	if (data->heredoc_delim)
		free(data->heredoc_delim);
	data->heredoc_delim = 0;
}
