/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 07:28:29 by rburri            #+#    #+#             */
/*   Updated: 2022/03/19 14:05:58 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_path(t_data *data)
{
	t_env	*tmp;

	tmp = data->environment;
	while (ft_strncmp("PATH", tmp->variable, 4))
		tmp = tmp->next;
	data->env_paths = tmp->value;
	if (data->env_paths == NULL)
	{
		ft_putendl_fd("env PATH not found", 2);
		return (1);
	}
	return (0);
}

static int	check_is_full_cmd(t_data *data, int i)
{
	if (access(data->cmd_table[i][0], F_OK) == 0)
	{
		data->cmd = ft_strdup(data->cmd_table[i][0]);
		return (1);
	}
	return (0);
}

int	get_cmd(t_data *data, int i)
{
	char	*tmp;
	char	*command;
	char	**paths;

	if (check_is_full_cmd(data, i))
		return (0);
	paths = data->cmd_paths;
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, data->cmd_table[i][0]);
		free(tmp);
		if (access(command, F_OK) == 0)
		{
			data->cmd = command;
			return (0);
		}
		free(command);
		paths++;
	}
	ft_putstr_fd(data->cmd_table[i][0], 2);
	ft_putendl_fd(": command not found", 2);
	return (1);
}

static int	check_is_full_cmd_hd(t_data *data, int i)
{
	if (access(data->heredoc_other_cmds[i][0], F_OK) == 0)
	{
		data->cmd = ft_strdup(data->heredoc_other_cmds[i][0]);
		return (1);
	}
	return (0);
}

int	get_cmd_hd(t_data *data, int i)
{
	char	*tmp;
	char	*command;
	char	**paths;
	
	if (check_is_full_cmd_hd(data, i))
		return (0);
	paths = data->cmd_paths;
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, data->heredoc_other_cmds[i][0]);
		free(tmp);
		if (access(command, F_OK) == 0)
		{
			data->cmd = command;
			return (0);
		}
		free(command);
		paths++;
	}
	ft_putstr_fd(data->heredoc_other_cmds[i][0], 2);
	ft_putendl_fd(": command not found", 2);
	return (1);
}
