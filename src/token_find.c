/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 07:32:37 by rburri            #+#    #+#             */
/*   Updated: 2022/03/03 10:03:50 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	find_token(t_data *data, char *cmd_str)
{
	int	i;
	int type;

	type = 1;
	i = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] ==  ' ')
			i++;
		if (cmd_str[i] == '\'' || cmd_str[i] == '\"')
		{
			if (create_token(data, send_quoted_string(cmd_str + i, &i), type))
			{
				ft_putstr_fd("Error create token\n", 2);
				return (1);
			}
			type = 2;
		}
		else if (cmd_str[i] == '|')
		{
			printf("came here\n");
			type = 1;
			data->num_of_pipe += 1;
			i++;
		}
		else if (cmd_str[i] == '<')
		{
			if (redir_in(data, cmd_str + i, &i))
				break;
		}
		else if (cmd_str[i] == '>')
		{
			if (redir_out(data, cmd_str + i, &i))
				break;
		}
		else if (cmd_str[i] == '$')
		{
			//do something
		}
		else 
		{
			if (create_token(data, send_unquoted_string(cmd_str + i, &i), type))
			{
				ft_putstr_fd("Error create token\n", 2);
				return (1);
			}
			type = 2;
		}
	}
	return (0);
}
