/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 07:32:37 by rburri            #+#    #+#             */
/*   Updated: 2022/03/17 14:36:38 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**create_cmd_table(int cnt_arg, t_token *cmd)
{
	t_token	*tmp;
	char	**cmd_table;
	int		j;

	j = 0;
	printf("cnt_arg : %d\n", cnt_arg);
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
		printf("create_cmd_table(heredoc or exec_cmd[%d] = ***%s***\n", j, cmd_table[j]);
		j++;
	}
	return (cmd_table);
}

static char	**cmd_split(t_data *data, int cnt_cmds, int cmd_num)
{
	t_token	*tmp;
	t_token	*tmp_arg;
	int		i;
	int		cnt_arg;
	int		cmd_to_find;

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

static char	**cmd_split_hd(t_data *data, int cnt_cmds, int cmd_num)
{
	t_token	*tmp;
	t_token	*tmp_arg;
	int		cnt_arg;
	int		i; // new
	int		cmd_to_find; // new

	i = 0; //
	cnt_arg = 0;
	cmd_to_find = (cnt_cmds - 1 - cmd_num); //
	tmp = data->token_stack;
	while (i++ < cmd_to_find)
		tmp = tmp->next; //
	if (tmp->args)
	{
		tmp_arg = tmp->args;
		while (tmp_arg)
		{
			tmp_arg = tmp_arg->next;
			cnt_arg++;
		}
	}
	// printf("seg before that?\n");
	// printf("cnt_arg: %d\n", cnt_arg);
	return (create_cmd_table(cnt_arg, tmp));
}

int	cmd_table(t_data *data)
{
	t_token	*tmp;
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

int	cmd_table_heredoc(t_data *data)
{
	t_token	*tmp;
	int		cnt_cmds;
	int		i;

	i = 1;
	cnt_cmds = 0;
	tmp = data->token_stack;
	while (tmp)
	{
		tmp = tmp->next;
		cnt_cmds++;
	}
	data->heredoc_other_cmds = (char ***)malloc(sizeof(char **) * (cnt_cmds + 2));
	if (data->heredoc_other_cmds == NULL)
		return (1);
	data->heredoc_other_cmds[cnt_cmds + 1] = 0;
	data->heredoc_other_cmds[0] = ft_split("/bin/echo -n .", ' ');
	printf("^^^%s\n", data->heredoc_other_cmds[0][0]);
	printf("^^^%s\n", data->heredoc_other_cmds[0][1]);
	while (i < (cnt_cmds + 1))
	{
	//	data->heredoc_other_cmds[1] = cmd_split_hd(data);
		data->heredoc_other_cmds[i] = cmd_split_hd(data, cnt_cmds, i - 1);
		if (data->heredoc_other_cmds[i] == NULL)
			return (1);
		i++;
	}
	i = 0;
	while (data->heredoc_other_cmds[i])
	{
		printf("cmd %d : *%s*\n", i, data->heredoc_other_cmds[i][0]);
//		printf("cmd 1 : *%s*\n", data->heredoc_other_cmds[1][0]);
//		printf("cmd 0 : *%s*\n", data->heredoc_other_cmds[0][0]);
		i++;
	}
	return (0);
}
