/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:11:19 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 10:14:02 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_echo(char **argv, int fd_output)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (argv[1] == 0)
	{
		write(fd_output, "\n", 1);
		return (0);
	}
	if (!ft_strncmp(argv[i], "-n", 2))
	{
		n_flag = 1;
		i++;
	}
	while (argv[i])
	{
		write(fd_output, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(fd_output, " ", 1);
		i++;
	}
	if (!n_flag)
		write(fd_output, "\n", 1);
	return (0);
}
