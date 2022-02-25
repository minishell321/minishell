/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 07:28:29 by rburri            #+#    #+#             */
/*   Updated: 2022/02/25 08:07:14 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	get_cmd(t_data *data)
{
	char	*tmp;
	char	*command;
	char	**paths;

	paths = data->cmd_paths;
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, data->cmd_args[0]);
		free(tmp);
		if (access(command, F_OK) == 0)
		{
			data->cmd = command;
			free(command);
			return (0);
		}
		// else
		// {
		// 	printf("%s :not found\n", data->cmd_args[0]);
		// 	break;
		// }
		free(command);
		paths++;
	}
	ft_putstr_fd(data->cmd_args[0], 2);
	ft_putendl_fd(": command not found", 2);
	return (1);
}
