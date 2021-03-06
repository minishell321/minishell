/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:35:33 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/15 10:24:09 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cnt_var(t_data *data)
{
	t_env	*tmp;
	int		num;

	num = 0;
	tmp = data->environment;
	while (tmp != 0)
	{
		tmp = tmp->next;
		num++;
	}
	return (num);
}

void	disp_env(t_data *data)
{
	t_env	*tmp;

	tmp = data->environment;
	while (tmp != 0)
	{
		printf("%s=%s\n", tmp->variable, tmp->value);
		tmp = tmp->next;
	}
}

int	create_env_entry(t_data *data, char *value, char *variable)
{
	t_env	*new_env_entry;
	t_env	*tmp;

	new_env_entry = malloc(sizeof(t_env));
	if (new_env_entry == NULL)
		return (1);
	new_env_entry->variable = variable;
	new_env_entry->value = value;
	new_env_entry->next = 0;
	if (data->environment == 0)
		data->environment = new_env_entry;
	else
	{
		tmp = data->environment;
		while (tmp->next != 0)
			tmp = tmp->next;
		tmp->next = new_env_entry;
	}
	return (0);
}

int	local_env(t_data *data, char **envp)
{
	int		i;
	int		start;
	char	*value;
	char	*variable;

	i = 0;
	while (envp[i] != 0)
	{
		value = 0;
		variable = 0;
		variable = ft_substr(envp[i], 0, (ft_strchr(envp[i], '=') - envp[i]));
		if (variable == 0)
			return (1);
		start = ft_strchr(envp[i], '=') - envp[i] + 1;
		value = ft_substr(envp[i], start, ft_strlen(envp[i]));
		if (value == 0)
			return (1);
		create_env_entry(data, value, variable);
		i++;
	}
	return (0);
}
