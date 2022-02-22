/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:13:13 by vbotev            #+#    #+#             */
/*   Updated: 2022/02/22 15:27:11 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Initialise the struct t_data, setting variables that are not yet assigned to 0 (or default)
int	init_data(t_data *data, char **envp)
{
	data->env_paths = find_path(envp);
	data->cmd_paths = ft_split(data->env_paths, ':');
	data->cmd_args = 0;
	data->cmd = 0;
	data->fd_input = 0;
	data->fd_output = 1;
	return (0);
}
