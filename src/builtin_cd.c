/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:29:13 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/03 18:03:26 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_cd(char *str)
{
	int		i;
	char	*cwd;
//	char	cwd[256];
	char	*path;

	cwd = 0;
	path = 0;
	printf("BUILTIN_CD - str: %s\n", str);
	cwd = malloc(256 * sizeof(char));
	if (cwd == 0)
	{
		printf("Error: malloc (builtin_cd) - 1\n");
		return (1);
	}
	if (getcwd(cwd, 256) == NULL)
	{
		printf("Error: getcwd\n");
		return (1);
	}
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '.' && str[i + 1] != '.')
	{
		if (chdir(cwd))
		{
			printf("Error: chdir\n");
			return (1);
		}
		printf("After cd, new cwd : %s\n", getcwd(cwd, 256));
	}
	else if (str[i] == '.' && str[i + 1] == '.')
	{
		path = ft_substr(cwd, 0, (ft_strrchr(cwd, '/') - cwd));
		if (path == 0)
		{
			printf("Error: malloc (builtin_cd) - 2\n");
			free(cwd);
			return (1);
		}
		printf("Cwd = %s\n", cwd);
		printf("Path = %s\n", path);
		if (chdir(path))
		{
			printf("Error: chdir\n");
			free(path);
			free(cwd);
			return (1);
		}
		printf("After cd, new cwd : %s\n", getcwd(cwd, 256));
		free(path);
	}
	else if (str[i] != '/')
	{
		// NOT A GREAT WAY OF DOING THIS!!! CORRECTION NEEDED!!!
		path = ft_strjoin(ft_strjoin(cwd, "/"), str);
		if (path == 0)
		{
			printf("Error: malloc (builtin_cd) - 3\n");
			free(cwd);
			return (1);
		}
		printf("Cwd = %s\n", cwd);
		printf("Path = %s\n", path);
		if (chdir(path))
		{
			printf("Error: chdir\n");
			free(path);
			free(cwd);
			return (1);
		 }
		printf("After cd, new cwd : %s\n", getcwd(cwd, 256));
		free(path);
	}
	else if (str[i] == '/')
	{
		printf("Cwd = %s\n", cwd);
        printf("Path = %s\n", str);
		if (chdir(str))
		{
			printf("Error: chdir\n");
			free(cwd);
			return (1);
		}
		printf("After cd, new cwd : %s\n", getcwd(cwd, 256));
	}
	free(cwd);
	return (0);
}
