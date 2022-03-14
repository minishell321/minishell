/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 07:28:29 by rburri            #+#    #+#             */
/*   Updated: 2022/03/14 10:23:21 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// not envp but struuct_env
int	find_path(t_data *data, char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	data->env_paths = *envp + 5;
	if (data->env_paths == NULL)
	{
		ft_putendl_fd("env PATH not found", 2);
		return (1);
	}
	return (0);
}

int	get_cmd(t_data *data, int i)
{
	char	*tmp;
	char	*command;
	char	**paths;

	if (access(data->cmd_table[i][0], F_OK) == 0)
	{
		data->cmd = ft_strdup(data->cmd_table[i][0]);
		return (0);
	}
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
