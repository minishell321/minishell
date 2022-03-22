/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:40:55 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/22 06:57:58 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	malloc_heredoc_str(t_data *data)
{
	data->heredoc_str = malloc(sizeof(char));
	if (data->heredoc_str == 0)
		return (1);
	data->heredoc_str[0] = 0;
	return (0);
}

static void	check_if_must_send(t_data *data, char **envp)
{
	if (!data->heredoc_other_cmds[1])
		free_heredoc(data);
	else
	{
		data->heredoc_other_cmds[0][2] = data->heredoc_str;
		exec_cmd_hd(data, envp);
		free_heredoc(data);
	}
}

static void	join_hd_str(t_data *data, char *str, int flag)
{
	char	*tmp;
	char	*str_endl;

	if (data->heredoc_ign_tab)
	{
		tmp = str;
		str = ft_strtrim(str, "\t");
		free (tmp);
	}
	if (flag == 0)
		str = find_dollars(str, data);
	str_endl = ft_strjoin(str, "\n");
	free(str);
	tmp = ft_strdup(data->heredoc_str);
	free(data->heredoc_str);
	data->heredoc_str = ft_strjoin(tmp, str_endl);
	free (str_endl);
	free (tmp);
}

int	heredoc_handler(t_data *data, char **envp)
{
	char	*str;
	char	*delim;
	int		flag;

	str = NULL;
	flag = 0;
	delim = data->heredoc_delim;
	if (ft_strchr(delim, '\'') || ft_strchr(delim, '\"'))
	{
		delim = ft_strtrim(data->heredoc_delim, "\'\"");
		flag = 1;
	}
	str = readline("> ");
	if (malloc_heredoc_str(data) || delim == 0)
		return (1);
	while (ft_strncmp(str, delim, ft_strlen(str)) || *str == '\0')
	{
		join_hd_str(data, str, flag);
		str = readline("> ");
	}
	if (flag)
		free (delim);
	free (str);
	check_if_must_send(data, envp);
	return (0);
}

int	check_is_heredoc(char *cmd_buf)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (cmd_buf[i])
	{
		if (cmd_buf[i] == '\"')
			d_quote++;
		if (cmd_buf[i] == '\'')
			s_quote++;
		if (cmd_buf[i] == '<' && cmd_buf[i + 1] == '<'
			&& s_quote % 2 == 0 && d_quote % 2 == 0)
			return (1);
		i++;
	}
	return (0);
}
