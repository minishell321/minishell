/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 07:32:37 by rburri            #+#    #+#             */
/*   Updated: 2022/03/23 07:08:16 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	pipe_cnt(t_data *data, int *type, int *i)
{
	*type = 1;
	*i += 1;
	data->num_of_pipe += 1;
}

int	find_token(t_data *data, char *cmd_str)
{
	int	i;
	int	type;

	type = 1;
	i = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] == ' ' || cmd_str[i] == '\t')
			i++;
		if (cmd_str[i] == '\'' || cmd_str[i] == '\"')
			if (create_token(data, send_quoted_str(cmd_str + i, &i), &type))
				return (1);
		if (cmd_str[i] == '|')
			pipe_cnt(data, &type, &i);
		if (cmd_str[i] == '<' || cmd_str[i] == '>')
			if (redir(data, cmd_str + i, &i))
				return (1);
		if (cmd_str[i] != ' ' && cmd_str[i] != '\0' && cmd_str[i] != '\t')
			if (create_token(data, send_unquoted_str(cmd_str + i, &i), &type))
				return (1);
	}
	return (0);
}
