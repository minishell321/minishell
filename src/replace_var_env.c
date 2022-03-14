/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 09:13:43 by rburri            #+#    #+#             */
/*   Updated: 2022/03/14 08:58:09 by rburri           ###   ########.fr       */
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
	while (str[i] != ' ' && str[i] != '\0' && str[i] != '\"')
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

char	*find_dollars(char *cmd_buf, t_data *data)
{
	char	*env;
	int		single_quote;
	int		env_finish;
	int		i;

	i = 0;
	env_finish = 0;
	single_quote = 0;
	while (cmd_buf[i])
	{
		if (cmd_buf[i] == '\'')
			single_quote++;
		if (cmd_buf[i] == '$' && single_quote % 2 == 0)
		{
			printf("going in\n");
			if (cmd_buf[i + 1] == ' ' || cmd_buf[i + 1] == '\0' || cmd_buf[i + 1] == '\"')
			{
				printf("going in strdup $\n");

				env = ft_strdup("$");
				env_finish++;
				cmd_buf = replace(cmd_buf, env, i, env_finish);
				printf("cmd_buf: ***%s***\n", cmd_buf);
			}
			else if (cmd_buf[i + 1] == '?' && (cmd_buf[i + 2] == ' ' || cmd_buf[ i + 2] == '\0'))
			{
				printf("going in itoa\n");

				env = ft_itoa(data->exit_code);
				env_finish += 2;
				cmd_buf = replace(cmd_buf, env, i, env_finish);
				printf("cmd_buf: ***%s***\n", cmd_buf);

			}
			else
			{
				printf("going in else\n");

				env = find_env(cmd_buf + i, data, &env_finish);
				printf("env: ***%s***\n", env);
				cmd_buf = replace(cmd_buf, env, i, env_finish);
				printf("cmd_buf: ***%s***\n", cmd_buf);

			}
			free(env);
		}
		i++;
	}
	return (cmd_buf);
}
