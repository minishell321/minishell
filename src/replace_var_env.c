/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 09:13:43 by rburri            #+#    #+#             */
/*   Updated: 2022/03/11 09:42:15 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_env(char *str, t_data *data, int *env_finish)
{
	t_env	*tmp;
	char	*env;
	int		i;

	i = 0;
	tmp = data->environment;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	*env_finish += i;
	env = ft_substr(str, 1, i - 1);
	i = ft_strlen(env);
	while (tmp != 0)
	{
		if (ft_strncmp(env, tmp->variable, i) == 0)
		{
			free(env);
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	free(env);
	return (ft_strdup(""));
}

static char	*replace(char *command_buf, char *env, int start, int finish)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_substr(command_buf, 0, start);
	tmp2 = ft_substr(command_buf, start + finish, ft_strlen(command_buf));
	tmp3 = ft_strjoin(tmp1, env);
	free(tmp1);
	tmp1 = ft_strjoin(tmp3, tmp2);
	free(tmp2);
	free(tmp3);
	free(command_buf);
	return (tmp1);
}

char	*find_dollars(char *command_buf, t_data *data)
{
	char	*env;
	int		single_quote;
	int		env_finish;
	int		i;

	i = 0;
	env_finish = 0;
	single_quote = 0;
	while (command_buf[i])
	{
		if (command_buf[i] == '\'')
			single_quote++;
		if (command_buf[i] == '$' && single_quote % 2 == 0)
		{
			env = find_env(command_buf + i, data, &env_finish);
			command_buf = replace(command_buf, env, i, env_finish);
			free(env);
		}
		i++;
	}
	return (command_buf);
}
