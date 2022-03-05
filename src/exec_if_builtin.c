/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_if_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 08:06:01 by rburri            #+#    #+#             */
/*   Updated: 2022/03/05 08:36:14 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_if_builtin(t_data *data, int i)
{
	if ((ft_strncmp(data->cmd_table[i][0], "echo", 4)) == 0)
	{
		builtin_echo(data->cmd_table[i]);
		return (1);
	}
	if ((ft_strncmp(data->cmd_table[i][0], "cd", 2)) == 0)
		return (1);
	if ((ft_strncmp(data->cmd_table[i][0], "pwd", 3)) == 0)
		return (1);
	if ((ft_strncmp(data->cmd_table[i][0], "export", 4)) == 0)
		return (1);
	if ((ft_strncmp(data->cmd_table[i][0], "unset", 4)) == 0)
		return (1);
	if ((ft_strncmp(data->cmd_table[i][0], "env", 4)) == 0)
		return (1);
	// if ((ft_strncmp(data->cmd_table[i][0], "exit", 4)) == 0)
	// 	return (1);
	return (0);
}
