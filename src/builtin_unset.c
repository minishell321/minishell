/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:22:05 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/21 15:43:43 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_unset(t_data *data, char *cmd)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = data->environment;
	while (tmp->next != 0)
	{
		if (ft_strncmp(cmd, tmp->next->variable, ft_strlen(cmd)) == 0
			&& ft_strlen(cmd) == ft_strlen(tmp->next->variable))
		{
			tmp2 = tmp->next->next;
			free(tmp->next);
			tmp->next = tmp2;
		}
		else if (ft_strncmp(cmd, tmp->variable, ft_strlen(cmd)) == 0
			&& ft_strlen(cmd) == ft_strlen(tmp->variable))
		{
			tmp2 = data->environment;
			data->environment = data->environment->next;
			free(tmp2);
		}
		if (tmp->next == 0)
			break ;
		tmp = tmp->next;
	}
}

int	builtin_unset(t_data *data)
{
	char	*cmd;

	if (data->cmd_table[0][1] == 0 || data->cmd_table[0][2])
		return (1);
	cmd = data->cmd_table[0][1];
	find_unset(data, cmd);
	return (0);
}
