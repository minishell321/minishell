/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 10:38:20 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 09:38:25 by rburri           ###   ########.fr       */
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
		// printf("data->cmd_table[%d]\n", i);
		j = 0;
		// SOMETHING MAKES SEGFAULT WHEN WHILE CHECKS CONDITION
		while (data->cmd_table[i][j] != NULL)
		{
			// printf("goes inner while\n");
			// printf("data->cmd_table[%d][%d] = %s\n", i, j, data->cmd_table[i][j]);
			free(data->cmd_table[i][j]);
			j++;
		}
		free(data->cmd_table[i]);
		i++;
	}
	// printf("-here-\n");
	// data->cmd_table = 0;
	free(data->cmd_table);
}

int	free_data(t_data *data)
{	
	int	i;

	if (data->cmd)
	{
		printf("free data->cmd\n");
		free(data->cmd);
	}
	i = 0;
	if (data->pipe_fds)
	{
		printf("free data->pipe_fds\n");
		while (i < data->num_of_pipe)
			free(data->pipe_fds[i++]);
		free(data->pipe_fds);
	}
	if (data->cmd_table)
	{
		printf("free data->cmd_table\n");
		free_cmd_table(data);
	}
	if (data->heredoc_other_cmds)
	{	
		printf("data->heredoc_other_cmds\n");
		free_heredoc_other_cmds(data);
	}
	if (data->process_ids)
	{
		printf("data->process_ids\n");
		free(data->process_ids);
	}
	if (data->cmd_paths)
	{
		printf("cmd_paths\n");
		while (data->cmd_paths[i])
			free(data->cmd_paths[i++]);
		free(data->cmd_paths);
	}
	printf("--here--\n");
	return (0);
}



int	free_env(t_data *data)
{
	t_env *tmp;
	t_env *tmp2;

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
