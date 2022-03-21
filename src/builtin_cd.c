/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:29:13 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/21 14:47:30 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_paths(char **arg, char *cwd)
{
	char	*path;

	path = 0;
	if (*arg[1] != '/')
	{
		ft_strlcat(cwd, "/", 256);
		path = ft_strjoin(cwd, arg[1]);
		if (path == 0)
			return (1);
		if (chdir(path))
		{
			perror("minishell");
			free(path);
			return (1);
		}
		free(path);
	}
	else if (chdir(arg[1]))
	{
		perror("minishell");
		return (1);
	}
	return (0);
}

int	handle_tilde_ext(char **arg, char *path)
{
	char	*path2;

	path2 = 0;
	if (arg[1] == 0 || *(arg[1] + 1) == 0)
	{
		if (chdir(path))
		{
			perror("minishell");
			return (1);
		}
	}
	else
	{
		path2 = ft_strjoin(path, (arg[1] + 1));
		if (path2 == 0)
			return (1);
		if (chdir(path2))
		{
			perror("minishell");
			free(path2);
			return (1);
		}
		free(path2);
	}
	return (0);
}

int	handle_tilde(char **arg, t_data *data)
{
	t_env	*tmp;
	int		ret;
	char	*path;

	tmp = data->environment;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, "HOME", ft_strlen("HOME")) == 0
			&& ft_strlen(tmp->variable) == ft_strlen("HOME"))
			path = ft_strdup(tmp->value);
		tmp = tmp->next;
	}
	if (path == 0)
		return (1);
	ret = handle_tilde_ext(arg, path);
	free(path);
	if (ret)
		return (1);
	return (0);
}

int	handle_symbols(char **arg, char *cwd, t_data *data)
{
	char	*path;

	path = 0;
	if (arg[1] == 0 || *arg[1] == '~' || *arg[1] == 0)
		return (handle_tilde(arg, data));
	else if (*(arg[1]) == '.' && *(arg[1] + 1) == 0)
	{
		if (chdir(cwd))
		{
			perror("minishell");
			return (1);
		}
	}
	else if (*arg[1] == '.' && *(arg[1] + 1) == '.' && *(arg[1] + 2) == 0)
	{
		path = ft_substr(cwd, 0, (ft_strrchr(cwd, '/') - cwd + 1));
		if (chdir(path))
		{
			perror("minishell");
			free(path);
			return (1);
		}
		free(path);
	}
	return (0);
}

int	builtin_cd(t_data *data)
{
	char	*cwd;
	char	**arg;

	cwd = 0;
	arg = data->cmd_table[0];
	cwd = malloc(256 * sizeof(char));
	if (cwd == 0 || getcwd(cwd, 256) == NULL)
		return (1);
	if (arg[1] == 0 || (*arg[1] == '.' && arg[1][1] == 0) || (*arg[1] == '~')
		|| (*arg[1] == '.' && *(arg[1] + 1) == '.' && *(arg[1] + 2) == 0))
	{
		if (handle_symbols(arg, cwd, data))
		{
			free(cwd);
			return (1);
		}
	}
	else if (handle_paths(arg, cwd))
	{
		free(cwd);
		return (1);
	}
	update_pwd(data, cwd);
	free (cwd);
	return (0);
}
