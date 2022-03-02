/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_to_strings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:27:39 by rburri            #+#    #+#             */
/*   Updated: 2022/03/02 09:47:45 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"

// int	cmd_table(t_data *data)
// {
// 	t_token	*tmp;
// 	tmp = data->cmds;
// 	int cnt_cmd;

// 	cnt_cmd = 0;
// 	while (tmp)
// 	{
// 		tmp = tmp->next;
// 		cnt_cmd++;
// 	}
// 	data->cmd_table = (char **)malloc(sizeof(char *) * cnt_cmd);
// 	if (data->cmd_table == NULL)
// 		return (1);
// 	tmp = data->cmds;
	
// 	return (0);
// }