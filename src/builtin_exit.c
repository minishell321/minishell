/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:00:13 by rburri            #+#    #+#             */
/*   Updated: 2022/03/21 11:12:05 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_exit(t_data *data)
{
	int exit_status;

	exit_status = 0;
	if ((ft_strncmp(data->cmd_table[0][0], "exit", 4)) == 0)
	{
		printf("exit\n");
		// if (data->cmd_table[0][1] && ft_isdigit(data->cmd_table[0][1]))
		// 	exit_status = ft_atoi(data->cmd_table[0][1]) % 256;
		// if (data->cmd_table[0][2])
			

		
		// // % 256 atoi
		// // if more than one arg = exit: too many arguments
		// // if no int = exit: fdsa: numeric argument required
		// free cmd_buf history
		// free_data(data);
		// free_env(data);
		exit (exit_status);
	}
	// return (0);
	// char	*tmp;
	// int		i;

	// tmp = ft_strtrim(command_buf, " ");
	// i = ft_strlen(tmp);	
	// if ((i == 4 && !ft_strncmp(tmp, "exit", 4)) || !ft_strncmp(tmp, "exit ", 5))
	// {
	// 	printf("exit\n");
	// 	free(tmp);
	// 	return (1);
	// }
	// free(tmp);
	// return (0);
}
