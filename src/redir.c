/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:25:22 by vbotev            #+#    #+#             */
/*   Updated: 2022/02/26 15:11:12 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// this function handles the redirections for << and >> and assigns the fd
// The << (here-document structure) is not complete
int	get_fd_multi(t_data *data, char *str, char redir_type)
{
	char	*delim;
	int		i;

	i = 0;
	if (*(++str) == ' ')
		str++;
	while (str[i] != ' ')
		i++;
	if (redir_type == '>')
	{
		str[i] = 0;
		data->fd_output = open(str, O_RDWR | O_APPEND, 0777);
		if (data->fd_output == -1)
			return (1);
	}
	else
	{
		ft_strlcpy(delim, str, i + 1);
		printf("delim = %s\n", delim);
	}
	return (0);
}

// this function handles the redirections for < and > and assigns the fd
int	get_fd(t_data *data, char *str, char redir_type)
{
	int	i;

	i = 0;
	if (*str == ' ')
		str++;
	while (str[i] != ' ')
		i++;
	str[i] = 0;
	if (redir_type == '<')
	{
		data->fd_input = open(str, O_RDONLY);
		if (data->fd_input == -1)
			return (1);
	}
	else if (redir_type == '>')
	{
		data->fd_output = open(str, O_RDWR | O_CREAT, 0777);
		if (data->fd_output == -1)
			return (1);
	}
	return (0);
}

int	redirect(t_data *data, char *command_buf)
{
	char	*tmp;

	tmp = ft_strchr(command_buf, '<');
	if (tmp++)
	{
		if (*tmp == '<')
		{
			if (get_fd_multi(data, tmp, '<'))
				return (1);
		}
		else if (get_fd(data, tmp, '<'))
			return (1);
	}
	tmp = ft_strchr(command_buf, '>');
	if (tmp++)
	{
		if (*tmp == '>')
		{
			if (get_fd_multi(data, tmp, '>'))
				return (1);
		}
		else if (get_fd(data, tmp, '>'))
			return (1);
	}
	return (0);
}
