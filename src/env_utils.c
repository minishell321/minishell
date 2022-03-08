/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:35:33 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/08 17:49:05 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void disp_env(t_data *data)
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

int local_env(t_data *data, char **envp)
{
	int		i;
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
		value = ft_substr(envp[i], (ft_strchr(envp[i], '=') - envp[i] + 1), ft_strlen(envp[i]));
		if (value == 0)
			return (1);
		create_env_entry(data, value, variable);
	//	printf("%s\n", envp[i]);
	//	printf("variable = %s\n", variable);
	//	printf("value = %s\n", value);
		i++;
	}

//	disp_env(data);
	return (1);
}
