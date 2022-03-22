/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 07:32:37 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 07:21:02 by rburri           ###   ########.fr       */
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

// void	print_token(t_data *data)
// {
// 	t_token	*tmp;
// 	tmp = data->token_stack;

// 	while (tmp != NULL)
// 	{
// 		printf("str: *%s*\n", tmp->str);
// 		if (tmp->args != NULL)
// 		{
// 			t_token *tmp_arg;
// 			tmp_arg = tmp->args;
// 			while (tmp_arg != NULL)
// 			{
// 				printf("args str : *%s*\n", tmp_arg->str);
// 				tmp_arg = tmp_arg->next;
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }
