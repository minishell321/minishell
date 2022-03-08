/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:29:13 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/08 10:58:21 by vbotev           ###   ########.fr       */
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
		printf("Cwd = %s\n", cwd);
		printf("Path = %s\n", path);
		if (chdir(path))
		{
			ft_putstr_fd("Error: chdir\n", 2);
			free(path);
			return (1);
		}
		printf("After cd, new cwd : %s\n", getcwd(cwd, 256));
		free(path);
	}
	else if (*arg[1] == '/')
	{
		printf("Cwd = %s\n", cwd);
		printf("Path = %s\n", arg[1]);
		if (chdir(arg[1]))
		{
			ft_putstr_fd("Error: chdir\n", 2);
			return (1);
		}
		printf("After cd, new cwd : %s\n", getcwd(cwd, 256));
	}
	return (0);
}

int	handle_tilde_ext(char**arg, char *cwd, char *path)
{
	char	*path2;

	path2 = 0;
	if (*(arg[1] + 1) == 0)
	{
		if (chdir(path))
		{
			ft_putstr_fd("Error: chdir\n", 2);
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
			ft_putstr_fd("Error: chdir\n", 2);
			free(path2);
			return (1);
		}
		free(path2);
	}
	return (0);
}

int	handle_tilde(char **arg, char *cwd)
{
	int		i;
	int		cnt;
	char	*path;

	i = -1;
	cnt = 0;
	path = 0;
	while (cwd[++i] != 0)
	{
		if (cwd[i] == '/')
			cnt++;
		if (cnt == 3)
			break ;
	}
	path = ft_substr(cwd, 0, i);
	if (path == 0)
		return (1);
	i = handle_tilde_ext(arg, cwd, path);
	free(path);
	if (i)
		return (1);
	printf("After cd, new cwd : %s\n", getcwd(cwd, 256));
	return (0);
}

int	handle_symbols(char **arg, char *cwd)
{
	char	*path;

	path = 0;
	if (*arg[1] == '~')
	{
		return (handle_tilde(arg, cwd));
	}
	else if (*(arg[1]) == '.' && *(arg[1] + 1) == 0)
	{
		if (chdir(cwd))
		{
			ft_putstr_fd("Error: chdir\n", 2);
			return (1);
		}
		printf("After cd, new cwd : %s\n", getcwd(cwd, 256));
	}
	else if (*arg[1] == '.' && *(arg[1] + 1) == '.' && *(arg[1] + 2) == 0)
	{
		path = ft_substr(cwd, 0, (ft_strrchr(cwd, '/') - cwd));
		if (path == 0)
			return (1);
		printf("Cwd = %s\n", cwd);
		printf("Path = %s\n", path);
		if (chdir(path))
		{
			ft_putstr_fd("Error: chdir\n", 2);
			free(path);
			return (1);
		}
		printf("After cd, new cwd : %s\n", getcwd(cwd, 256));
		free(path);
	}
	return (0);
}

int	builtin_cd(char **arg)
{
	char	*cwd;

	cwd = 0;
	cwd = malloc(256 * sizeof(char));
	if (cwd == 0)
		return (1);
	if (getcwd(cwd, 256) == NULL)
	{
		ft_putstr_fd("Error: getcwd\n", 2);
		return (1);
	}
	if (arg[1] == 0 || arg[2] != 0)
		return (1);
	if ((*arg[1] == '.' && arg[1][1] == 0) || (*arg[1] == '~')
		|| (*arg[1] == '.' && *(arg[1] + 1) == '.' && *(arg[1] + 2) == 0))
	{
		if (handle_symbols(arg, cwd))
		{
			free(cwd);
			return (1);
		}
	}
	else
	{
		if (handle_paths(arg, cwd))
		{
			free(cwd);
			return (1);
		}
	}
	free(cwd);
	return (0);
}
