/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 08:27:23 by rburri            #+#    #+#             */
/*   Updated: 2022/03/11 11:28:21 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	redir_out(t_data *data, char *str, int *i)
{
	if (*(str + 1) == '>')
	{
		if (get_fd_out_append(data, str, i))
			return (1);
	}
	else
	{
		if (get_fd_out(data, str, i))
			return (1);
	}
	return (0);
}

static int	redir_in(t_data *data, char *str, int *i)
{
	if (*(str + 1) == '<')
	{
		if (get_fd_here_doc(data, str, i))
			return (1);
	}
	else
	{
		if (get_fd_in(data, str, i))
			return (1);
	}
	return (0);
}

int	redir(t_data *data, char *str, int *i)
{	
	if (*str == '<')
	{
		if (redir_in(data, str, i))
			return (1);
	}
	else if (*str == '>')
	{
		if (redir_out(data, str, i))
			return (1);
	}
	return (0);
}
