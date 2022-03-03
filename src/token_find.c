/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 07:32:37 by rburri            #+#    #+#             */
/*   Updated: 2022/03/03 08:31:40 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// This function is meant to test how a table of strings could be created by having
// the first element in the table as the cmd and the remaining elements being the
// arg which correspond to this command
// !!! CURRENTLY THE FUNCTION HAS A BUG AND IS NOT CORRECTLY INCLUDING THE BUGS
// !!! ALSO AS IT IS MEANT AS A TEST IT ONLY HANDLES ONE COMMAND BUT THE CONCEPT CAN
// BE EXTENDED USING A LINKED LIST
char **cmd_split(t_data *data, int cnt_cmds, int cmd_num)
{
	t_token *tmp;
	char	**cmd_table;
	int j = 0;
	int i = 0;
	int cnt_arg = 0;
	int cmd_to_find;


	cmd_to_find = (cnt_cmds - 1 - cmd_num);
	tmp = data->token_stack;
	while (i++ < cmd_to_find)
		tmp = tmp->next;
	if (tmp->args)
	{
		t_token *tmp_arg;
		tmp_arg = tmp->args;
		while (tmp_arg)
		{
			tmp_arg = tmp_arg->next;
			cnt_arg++;
		}
	}
	// printf("cnt_arg = %d\n", cnt_arg);
	cmd_table = (char **)malloc(sizeof(char *) * (cnt_arg + 2));
	if (cmd_table == NULL)
		return (NULL);
	cmd_table[0] = tmp->str;
	tmp = tmp->args;
	cmd_table[cnt_arg + 1] = NULL;
	while (cnt_arg > 0)
	{
		// printf("cmd_table[%d] = %s\n", cnt_arg, tmp->str);
		cmd_table[cnt_arg--] = tmp->str;
		tmp = tmp->next;
	}
	j = 0;
	while (cmd_table[j] != 0)
	{
		printf("cmd_table[%d] = %s\n", j, cmd_table[j]);
		j++;
	}



	/*
	while (tmp)
	{
		printf("cmd[%d]: %s\n", j, tmp->str);
		if (tmp->args)
		{
			t_token *tmp_arg;
			tmp_arg = tmp->args;
			int i = 0;
			while (tmp_arg)
			{
				printf("arg[%d]: %s\n", i, tmp_arg->str);
				tmp_arg = tmp_arg->next;
				i++;
			}
		}
		tmp = tmp->next;
		j++;
	}
	*/
	return (cmd_table);
}

int cmd_table(t_data *data)
{
	t_token *tmp;
	int		cnt_cmds;
	int		i;
	
	i = 0;
	cnt_cmds = 0;
	tmp = data->token_stack;
	while (tmp)
	{
		tmp = tmp->next;
		cnt_cmds++;
	}
	data->cmd_table = (char ***)malloc(sizeof(char **) * (cnt_cmds + 1));
	if (data->cmd_table == NULL)
		return (1);
	data->cmd_table[cnt_cmds] = 0;
	while (i < cnt_cmds)
	{
		printf("CMD[%d]\n", i);
		data->cmd_table[i] = cmd_split(data, cnt_cmds, i);
		i++;
	}
	return (0);
}

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
			{
				ft_putstr_fd("Error redirection\n", 2);
			}
		}
		else if (cmd_str[i] == '>')
		{
			// printf("---HERE--- i = %d; cmd_str = %s\n", i, cmd_str+i);
			if (redir_out(data, cmd_str + i, &i))
			{
				ft_putstr_fd("Error redirection\n", 2);
			}
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
	if (cmd_table(data))
	{
		printf("Error: generation of command table\n");
		return (1);
	}
	return (0);
}
