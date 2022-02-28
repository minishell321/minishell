/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:25:22 by vbotev            #+#    #+#             */
/*   Updated: 2022/02/28 16:29:27 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// this function handles the redirections for << and >> and assigns the fd
// The << (here-document structure) is not complete
int	get_fd_multi(t_data *data, char *str, char redir_type)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = str - 1;
	if (*(++str) == ' ')
		str++;
	while (str[i] != ' ' && str[i] != 0)
		i++;
	if (redir_type == '>')
	{
		str[i] = 0;
		data->fd_output = open(str, O_RDWR | O_APPEND, 0777);
		free(cpy);
		if (data->fd_output == -1)
			return (1);
	}
	else
	{
		printf("HEREDOC delim = %s\n", str);
		free(cpy);
	}
	return (0);
}

// this function handles the redirections for < and > and assigns the fd
int	get_fd(t_data *data, char *str, char redir_type)
{
	char	*cpy;
	int		i;

	i = 0;
	cpy = str - 1;
	if (*str == ' ')
		str++;
	while (str[i] != ' ' && str[i] != 0)
		i++;
	str[i] = 0;
	if (redir_type == '<')
	{
		data->fd_input = open(str, O_RDONLY);
		free(cpy);
		if (data->fd_input == -1)
			return (1);
	}
	else if (redir_type == '>')
	{
		data->fd_output = open(str, O_RDWR | O_CREAT, 0777);
		free(cpy);
		if (data->fd_output == -1)
			return (1);
	}
	return (0);
}

int	redirect(t_data *data, char *command_buf)
{
	char	*tmp;

	if (ft_strchr(command_buf, '<'))
	{
		tmp = ft_strdup(ft_strchr(command_buf, '<'));
		if (*(++tmp) == '<')
		{
			if (get_fd_multi(data, tmp, '<'))
				return (1);
		}
		else if (get_fd(data, tmp, '<'))
			return (1);
	}
	if (ft_strchr(command_buf, '>'))
	{
		tmp = ft_strdup(ft_strchr(command_buf, '>'));
		if (*(++tmp) == '>')
		{
			if (get_fd_multi(data, tmp, '>'))
				return (1);
		}
		else if (get_fd(data, tmp, '>'))
			return (1);
	}
	return (0);
}
