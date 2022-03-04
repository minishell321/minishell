/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 07:32:37 by rburri            #+#    #+#             */
/*   Updated: 2022/03/03 10:03:50 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char **create_cmd_table(int cnt_arg, t_token *cmd)
{
    char	**cmd_table;
    t_token *tmp;
    int j = 0;

    cmd_table = (char **)malloc(sizeof(char *) * (cnt_arg + 2));
	if (cmd_table == NULL)
		return (NULL);
	cmd_table[0] = cmd->str;
	tmp = cmd->args;
	cmd_table[cnt_arg + 1] = NULL;
	while (cnt_arg > 0)
	{
		cmd_table[cnt_arg--] = tmp->str;
		tmp = tmp->next;
	}
	while (cmd_table[j] != 0)
	{
		printf("cmd_table[%d] = %s\n", j, cmd_table[j]);
		j++;
	}
	return (cmd_table);
}

static char **cmd_split(t_data *data, int cnt_cmds, int cmd_num)
{
	t_token *tmp;
	t_token *tmp_arg;
	int i;
	int cnt_arg;
	int cmd_to_find;

    i = 0;
    cnt_arg = 0;
	cmd_to_find = (cnt_cmds - 1 - cmd_num);
	tmp = data->token_stack;
	while (i++ < cmd_to_find)
		tmp = tmp->next;
	if (tmp->args)
	{
		tmp_arg = tmp->args;
		while (tmp_arg)
		{
			tmp_arg = tmp_arg->next;
			cnt_arg++;
		}
	}
	return (create_cmd_table(cnt_arg, tmp));
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
        if (data->cmd_table[i] == NULL)
            return (1);
		i++;
	}
	return (0);
}