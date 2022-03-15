/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 08:13:28 by rburri            #+#    #+#             */
/*   Updated: 2022/03/15 16:03:08 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	token_handler(t_data *data)
{
	if (cmd_table(data))
	{
		ft_putstr_fd("Error: generation of command table\n", 2);
		if (data->token_stack)
			free_token_stack(data);
		return (1);
	}
	if (data->token_stack)
		free_token_stack(data);
	init_pids_arr(data);
	if (data->num_of_pipe > 0)
	{
		if (init_pipe_fds(data))
		{
			ft_putstr_fd("Error, create pipe_fds\n", 2);
			return (1);
		}
	}
	return (0);
}
