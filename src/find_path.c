/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 08:23:31 by rburri            #+#    #+#             */
/*   Updated: 2022/03/21 08:23:35 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_path(t_data *data)
{
	t_env	*tmp;

	tmp = 0;
	tmp = data->environment;
	while (tmp != NULL)
	{
		if (ft_strncmp("PATH", tmp->variable, 4))
		{
			data->env_paths = tmp->value;
			return (0);
		}
		tmp = tmp->next;
	}
	ft_putendl_fd("env PATH not found", 2);
	return (1);
}
