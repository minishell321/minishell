/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 08:31:07 by rburri            #+#    #+#             */
/*   Updated: 2022/03/17 09:31:20 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_token(t_data *data, char *str, int *type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (1);
	new_token->type = *type;
	new_token->str = str;
	new_token->next = NULL;
	new_token->args = NULL;
	if (new_token->type == CMD)
	{
		new_token->next = data->token_stack;
		data->token_stack = new_token;
	}
	else if (new_token->type == ARG)
	{
		new_token->next = data->token_stack->args;
		data->token_stack->args = new_token;
	}
	*type = 2;
	return (0);
}

char	*send_quoted_str(char *str, int *i)
{
	char	*new_str;
	int		j;
	int		k;

	j = 0;
	k = 1;
	while (str[j] != str[k])
		k++;
	new_str = (char *)malloc(sizeof(char) * k);
	if (new_str == NULL)
		return (NULL);
	while (j < k - 1)
	{
		new_str[j] = str[j + 1];
		j++;
	}
	new_str[j] = '\0';
	*i += (k + 1);
	return (new_str);
}

char	*send_unquoted_str(char *str, int *i)
{
	char	*new_str;
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (str[k] && str[k] != ' ')
		k++;
	printf("send_unquote k : %d\n", k);
	new_str = (char *)malloc(sizeof(char) * k + 1);
	if (new_str == NULL)
		return (NULL);
	while (j < k)
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j] = '\0';
	while (str[k] == ' ')
		k++;
	*i += (k);
	return (new_str);
}

void	free_token_stack(t_data *data)
{
	t_token	*tmp;
	t_token	*tmp_arg;

	while (data->token_stack)
	{
		tmp = data->token_stack;
		data->token_stack = data->token_stack->next;
		if (tmp->args)
		{
			while (tmp->args)
			{
				tmp_arg = tmp->args;
				tmp->args = tmp->args->next;
				free(tmp_arg);
			}
		}
		free(tmp);
	}
}
