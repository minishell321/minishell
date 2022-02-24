/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 09:28:50 by rburri            #+#    #+#             */
/*   Updated: 2022/02/24 11:26:56 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_all(t_data *data)
{	
	int	i;

	i = 0;
	while (data->cmd_paths[i])
		free(data->cmd_paths[i++]);
	free(data->cmd_paths);
	i = 0;
	if (data->num_of_pipe > 0)
	{
		while (i < data->num_of_pipe)
			free(data->pipe_fds[i]);
		free(data->pipe_fds);
	}

	return (0);
}
