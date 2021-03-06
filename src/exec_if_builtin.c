/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_if_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 08:06:01 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 10:19:26 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_if_builtin(t_data *data)
{
	if (data->num_of_pipe > 0)
	{
		ft_putstr_fd("Error, pipe with built-ins no supported\n", 2);
		return (1);
	}
	if ((ft_strncmp(data->cmd_table[0][0], "echo", 5)) == 0)
		return (builtin_echo(data->cmd_table[0], data->fd_output));
	if ((ft_strncmp(data->cmd_table[0][0], "cd", 3)) == 0)
		return (builtin_cd(data));
	if ((ft_strncmp(data->cmd_table[0][0], "pwd", 4)) == 0)
		return (builtin_pwd(data->fd_output));
	if ((ft_strncmp(data->cmd_table[0][0], "export", 7)) == 0)
		return (builtin_export(data));
	if ((ft_strncmp(data->cmd_table[0][0], "unset", 6)) == 0)
		return (builtin_unset(data));
	if ((ft_strncmp(data->cmd_table[0][0], "env", 4)) == 0)
		return (builtin_env(data));
	if ((ft_strncmp(data->cmd_table[0][0], "exit", 5)) == 0)
		return (1);
	return (0);
}

int	check_if_builtin(t_data *data)
{
	if (data->cmd_table[0])
	{
		if ((ft_strncmp(data->cmd_table[0][0], "echo", 5)) == 0)
			return (1);
		if ((ft_strncmp(data->cmd_table[0][0], "cd", 3)) == 0)
			return (1);
		if ((ft_strncmp(data->cmd_table[0][0], "pwd", 4)) == 0)
			return (1);
		if ((ft_strncmp(data->cmd_table[0][0], "export", 7)) == 0)
			return (1);
		if ((ft_strncmp(data->cmd_table[0][0], "unset", 6)) == 0)
			return (1);
		if ((ft_strncmp(data->cmd_table[0][0], "env", 4)) == 0)
			return (1);
		if ((ft_strncmp(data->cmd_table[0][0], "exit", 5)) == 0)
			return (1);
	}
	return (0);
}
