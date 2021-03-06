/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 08:22:37 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 11:58:08 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	split_path(t_data *data)
{
	data->cmd_paths = ft_split(data->env_paths, ':');
	if (data->cmd_paths == NULL)
	{
		ft_putstr_fd("Error, split env_paths\n", 2);
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
	if (find_path(data) || split_path(data))
		return (1);
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
	perror("minishell");
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
	if (find_path(data) || split_path(data))
		return (1);
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
