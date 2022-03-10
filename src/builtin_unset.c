/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:22:05 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/10 18:04:48 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int builtin_unset(t_data *data)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*cmd;

	if (data->cmd_table[0][1] == 0 || data->cmd_table[0][2])
		return (1);
	tmp = data->environment;
	cmd = data->cmd_table[0][1];
	while (tmp->next != 0)
	{
		if (ft_strncmp(cmd, tmp->next->variable, ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen(tmp->next->variable))
		{
		//	printf("HERE - next->variable = %s\n", tmp->next->variable);
		//	if (tmp->next->next == 0)
		//		tmp2 = 0;
		//	else
		//	{
		//		tmp2 = tmp->next->next;
		//	}
			tmp2 = tmp->next->next;
			free(tmp->next);
			tmp->next = tmp2;
		//	printf("ENDED CORRECTLY\n");
		}
		else if (ft_strncmp(cmd, tmp->variable, ft_strlen(cmd)) == 0 && ft_strlen(cmd) == ft_strlen(tmp->variable))
		{
			tmp2 = data->environment;
			data->environment = data->environment->next;
			free(tmp2);
		}
		if (tmp->next == 0)
			break;
		tmp = tmp->next;
	}
	return (0);
}
