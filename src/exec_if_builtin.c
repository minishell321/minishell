/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_if_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 08:06:01 by rburri            #+#    #+#             */
/*   Updated: 2022/03/08 17:48:42 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_if_builtin(t_data *data, int i)
{
	if ((ft_strncmp(data->cmd_table[i][0], "echo", 4)) == 0)
	{
		return (builtin_echo(data->cmd_table[i], data->fd_output));
	}
	if ((ft_strncmp(data->cmd_table[i][0], "cd", 2)) == 0)
	{
		return (builtin_cd(data->cmd_table[i]));
	}
	if ((ft_strncmp(data->cmd_table[i][0], "pwd", 3)) == 0)
	{
		return (builtin_pwd(data->cmd_table[i], data->fd_output));
	}
	if ((ft_strncmp(data->cmd_table[i][0], "export", 6)) == 0)
		return (1);
	if ((ft_strncmp(data->cmd_table[i][0], "unset", 5)) == 0)
		return (1);
	if ((ft_strncmp(data->cmd_table[i][0], "env", 3)) == 0)
	{
		return (builtin_env(data));
	}
	// if ((ft_strncmp(data->cmd_table[i][0], "exit", 4)) == 0)
	// 	return (1);
	return (0);
}
