/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:40:55 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/15 18:08:05 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc_handler(t_data *data)
{
	char	*delim;
	char	*str;
	char	*tmp;
	int		i;
	
	i = 0;
//	printf("HERE - heredoc_delim: %s\n", data->heredoc_delim);
	delim = data->heredoc_delim;
	str = data->command_buf;
	if (data->heredoc_str == 0)
	{
		data->heredoc_str = malloc(sizeof(char));
		if (data->heredoc_str == 0)
			return (1);
		data->heredoc_str[0] = 0;
	}
//	if (ft_strchr(delim, '\'') || ft_strchr(delim, '\"'))
//	{
	//	printf("PRIOR TO STRNCMP\n");
		if (ft_strncmp(str, delim, ft_strlen(str))
			&& ft_strlen(str) != ft_strlen(delim))
		{
			tmp = data->heredoc_str;
			data->heredoc_str = ft_strjoin(tmp, "\n");
			free (tmp);
			tmp = data->heredoc_str;
			data->heredoc_str = ft_strjoin(tmp, str);
			free (tmp);
	//		printf("THE STRING IS: %s\n", data->heredoc_str);
		}
		else
		{
			tmp = data->heredoc_str;
			data->heredoc_str = ft_strjoin(tmp, "\n");
			free (tmp);
			ft_putstr_fd(data->heredoc_str, data->fd_output);
			free (data->heredoc_str);
			data->heredoc_str = 0;
			printf("***HEREDOC END\n");
			while (data->heredoc_other_cmds[0][i] != 0)
			{
				printf("heredoc_other_cmds[0][%d]: %s\n", i, data->heredoc_other_cmds[0][i]);
				i++;
			}
			free(data->heredoc_delim);
			data->heredoc_delim = 0;
			data->heredoc = 0;
		}
//	}
	return (0);
}
