/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:00:55 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/15 10:09:52 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_pwd(t_data *data, char *cwd)
{
	t_env	*tmp;

	tmp = data->environment;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, "OLDPWD", ft_strlen("OLDPWD")) == 0
			&& ft_strlen(tmp->variable) == ft_strlen("OLDPWD"))
		{
			if (tmp->value)
				free (tmp->value);
			tmp->value = cwd;
		}
		else if (ft_strncmp(tmp->variable, "PWD", ft_strlen("PWD")) == 0
			&& ft_strlen(tmp->variable) == ft_strlen("PWD"))
		{
			free (tmp->value);
			tmp->value = getcwd(ft_strdup(cwd), 256);
		}
		tmp = tmp->next;
	}
}

int	cpy_env(t_data *data, char **cpy_env_variables)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = data->environment;
	while (tmp != 0)
	{
		cpy_env_variables[i] = ft_strdup(tmp->variable);
		if (cpy_env_variables[i++] == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	sort_env(char **cpy)
{
	int		i;
	int		j;
	char	*str_tmp;

	i = 0;
	while (cpy[i])
	{
		j = 0;
		while (cpy[j])
		{
			if (ft_strncmp(cpy[i], cpy[j], ft_strlen(cpy[i])) < 0)
			{
				str_tmp = cpy[i];
				cpy[i] = cpy[j];
				cpy[j] = str_tmp;
			}
			j++;
		}
		i++;
	}
}
