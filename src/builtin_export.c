/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 13:15:48 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/14 17:17:25 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	display_sorted(t_data *data, char **cpy)
{
	t_env	*tmp;
	int		i;

	i = 0;
	while (cpy[i])
	{
		tmp = data->environment;
		while (tmp != 0)
		{
			if (!ft_strncmp(cpy[i], tmp->variable, ft_strlen(cpy[i]))
				&& ft_strlen(tmp->variable) == ft_strlen(cpy[i]))
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
}

// FUNCTION RETURNS 1 IF THE VARIABLE NAME ALREADY EXISTS, ELSE IT RETURNS 0
int	find_var(t_data *data, char *var, char *val)
{
	t_env	*tmp;

	tmp = data->environment;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, var, ft_strlen(var)) == 0
			&& ft_strlen(tmp->variable) == ft_strlen(var))
		{
			if (val != 0)
			{
				free (tmp->value);
				tmp->value = val;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	identify_env(t_data *data, char *cmd)
{
	char	*val;
	char	*var;

	val = 0;
	var = 0;
	if (ft_strchr(cmd, '='))
	{
		var = ft_substr(cmd, 0, ft_strchr(cmd, '=') - cmd);
		val = ft_substr(cmd, ft_strchr(cmd, '=') - cmd + 1, ft_strlen(cmd));
		if (val == 0 || var == 0)
			return (1);
		if (find_var(data, var, val))
			free (var);
		else
			create_env_entry(data, val, var);
	}
	else
	{
		var = ft_strdup(cmd);
		if (find_var(data, var, NULL))
			free (var);
		else
			create_env_entry(data, NULL, var);
	}
	return (0);
}

int	add_to_env(t_data *data)
{
	int		i;
	char	*cmd;

	i = 0;
	while (data->cmd_table[0][++i])
	{
		cmd = data->cmd_table[0][i];
		if (ft_isalpha(*cmd) == 0 || *cmd == 95)
		{
			ft_putstr_fd("not a valid identifier\n", 2);
			return (1);
		}
		if (identify_env(data, cmd))
			return (1);
	}
	return (0);
}

int	builtin_export(t_data *data)
{
	int		i;
	char	**cpy_env_variables;

	cpy_env_variables = 0;
	cpy_env_variables = malloc(sizeof(char *) * (cnt_var(data) + 1));
	if (cpy_env_variables == 0 || cpy_env(data, cpy_env_variables))
		return (1);
	cpy_env_variables[cnt_var(data)] = 0;
	sort_env(cpy_env_variables);
	if (data->cmd_table[0][1] == 0)
		display_sorted(data, cpy_env_variables);
	else
	{
		if (add_to_env(data))
			return (1);
	}
	i = 0;
	while (cpy_env_variables[i])
		free(cpy_env_variables[i++]);
	free(cpy_env_variables);
	return (0);
}
