/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 09:13:43 by rburri            #+#    #+#             */
/*   Updated: 2022/03/10 10:19:48 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// 1 - find if command_buf contains $ outside '

// 2 - replace all $ by their value

// 3 - return the new string (in struct?)

char	*find_env(char *str, t_data *data)
{
	t_env	*tmp;
	char	*env;
	int		i;

	i = 0;
	tmp = data->environment;
	while (str[i] == ' ' || str[i] == '\0')
		i++;
	env = ft_substr(str, 1, i);
	i = ft_strlen(env);
	while (tmp != 0)
	{
		if (ft_strncmp(env, tmp->variable, i) == 0)
	}
	// check if find in t_env variable
	//if yes return value || return " "
}

int	find_dollars(char *command_buf, t_data *data)
{
	int	i;
	int	single_quote;
	char *env;

	i = 0;
	single_quote = 0;
	while (command_buf[i])
	{
		if (command_buf[i] == '\'')
			single_quote++;
		if (command_buf[i] == '$' && single_quote % 2 == 0)
			env = find_env(command_buf + i, data);
	}
	
}


