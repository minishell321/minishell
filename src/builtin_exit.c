/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:00:13 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 08:47:29 by rburri           ###   ########.fr       */
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

int	check_exit(t_data *data)
{
	if ((ft_strncmp(data->cmd_table[0][0], "exit\0", 5) == 0))
	{
		printf("exit\n");
		if (data->cmd_table[0][2])
		{
			printf("exit: too many arguments\n");
			return (0);
		}
		if (!data->cmd_table[0][1])
			data->exit_code = 0;
		else if (data->cmd_table[0][1] && str_isdigit(data->cmd_table[0][1]))
			data->exit_code = ft_atoi(data->cmd_table[0][1]) % 256;
		else if (data->cmd_table[0][1] && !str_isdigit(data->cmd_table[0][1]))
		{
			printf("exit: %s: numeric argument required\n",
				data->cmd_table[0][1]);
			data->exit_code = 255;
		}
		if (data)
			free_data(data);
		if (data->command_buf)
			free(data->command_buf);
		return (1);
	}
	return (0);
}
