/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:49:06 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/18 09:53:06 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_pwd(int fd_output)
{
	char	*cwd;

	cwd = 0;
	cwd = malloc(256 * sizeof(char));
	if (cwd == 0)
		return (1);
	if (getcwd(cwd, 256) == NULL)
	{
		ft_putstr_fd("Error: getcwd\n", 2);
		return (1);
	}
	ft_putstr_fd(cwd, fd_output);
	write(fd_output, "\n", 1);
	free (cwd);
	return (0);
}
