/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:17:31 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/21 15:10:39 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->environment;
	while (tmp != 0)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->variable, data->fd_output);
			ft_putstr_fd("=", data->fd_output);
			ft_putstr_fd(tmp->value, data->fd_output);
			ft_putstr_fd("\n", data->fd_output);
		}
		tmp = tmp->next;
	}
	return (0);
}
