/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 10:11:19 by rburri            #+#    #+#             */
/*   Updated: 2022/03/03 10:16:43 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int echo(char **argv)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!ft_strncmp(argv[i], "-n", 2))
	{
		n_flag = 1;
		i++;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (n_flag != 0)
		write(1, "\n", 1);
	return (0);
}
