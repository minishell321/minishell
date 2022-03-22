/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:00:13 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 11:56:50 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	free_exit(t_data *data)
{
	if (data->environment)
		free_env(data);
	if (data)
		free_data(data);
	if (data->command_buf)
		free(data->command_buf);
}

static void	set_status_exit(t_data *data)
{
	if (!data->cmd_table[0][1])
		data->exit_code = 0;
	else if (data->cmd_table[0][1] && str_isdigit(data->cmd_table[0][1]))
		data->exit_code = ft_atoi(data->cmd_table[0][1]) % 256;
	else if (data->cmd_table[0][1] && !str_isdigit(data->cmd_table[0][1]))
	{
		printf("minishell: %s: numeric argument required\n",
			data->cmd_table[0][1]);
		data->exit_code = 255;
	}
}

int	check_exit(t_data *data)
{
	int	i;

	i = 0;
	if ((ft_strncmp(data->cmd_table[0][0], "exit", 5) == 0))
	{
		printf("exit\n");
		while (data->cmd_table[0][i])
			i++;
		if (i > 2 && str_isdigit(data->cmd_table[0][1]))
		{
			printf("minishell: exit: too many arguments\n");
			return (0);
		}
		set_status_exit(data);
		free_exit(data);
		return (1);
	}
	return (0);
}
