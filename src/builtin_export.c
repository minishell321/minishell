/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:15:48 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/10 17:17:53 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_export(t_data *data)
{
	t_env	*tmp;
	int		num;
	int		i;
	int		j;
	char	*str_tmp;
	char	**cpy_env_variables;

	num = 0;
	i = 0;
	tmp = data->environment;
	while (tmp != 0)
	{
		tmp = tmp->next;
		num++;
	}
	cpy_env_variables = malloc(sizeof(char *) * (num  + 1));
	if (cpy_env_variables == 0)
		return (1);
	cpy_env_variables[num] = 0;
	tmp = data->environment;
	while (tmp != 0)
	{
		cpy_env_variables[i] = ft_strdup(tmp->variable);
		if (cpy_env_variables[i] == 0)
			return (1);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	while (cpy_env_variables[i])
	{
		j = 0;
		while (cpy_env_variables[j])
		{
			if (ft_strncmp(cpy_env_variables[i], cpy_env_variables[j], ft_strlen(cpy_env_variables[i])) < 0)
			{
				str_tmp = cpy_env_variables[i];
				cpy_env_variables[i] = cpy_env_variables[j];
				cpy_env_variables[j] = str_tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (cpy_env_variables[i])
	{
		tmp = data->environment;
		while (tmp != 0)
		{
			if (!ft_strncmp(cpy_env_variables[i], tmp->variable, ft_strlen(cpy_env_variables[i]) ) && ft_strlen(tmp->variable) == ft_strlen(cpy_env_variables[i]))
			{
				ft_putstr_fd("declare -x ", data->fd_output);
				ft_putstr_fd(tmp->variable, data->fd_output);
				ft_putstr_fd("=\"", data->fd_output);
				ft_putstr_fd(tmp->value, data->fd_output);
				ft_putstr_fd("\"\n", data->fd_output);
			}
			tmp = tmp->next;
		}
		i++;
	}
	i = 0;
	while (cpy_env_variables[i])
	{
//		printf("%s\n", cpy_env_variables[i]);
		free(cpy_env_variables[i++]);
	}
	free(cpy_env_variables);
	return (0);
}
