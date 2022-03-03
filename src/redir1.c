/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 08:27:23 by rburri            #+#    #+#             */
/*   Updated: 2022/03/03 08:27:45 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int get_fd_out_append(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*fd_name;

	j = 0;
	k = 0;
	while (str[j] == '>' || str[j] == ' ')
		j++;
//	while (str[k] != ' ')
	while (str[k + j] != ' ' && str[k + j] != '\0')
		k++;
	*i += (j + k);
	fd_name = (char *)malloc(sizeof(char) * k + 1);
	if (fd_name == NULL)
		return (1);
	fd_name[k--] = '\0';
	while (k >= 0)
	{
		fd_name[k] = str[k + j];
		k--;
	}
	data->fd_output = open(fd_name, O_RDWR | O_APPEND, 0777);
	if (data->fd_output == -1)
	{
			free(fd_name);
			return (1);
	}
	free(fd_name);
	return (0);	
}

int get_fd_here_doc(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*delim;

	j = 0;
	k = 0;

	while (str[j] == '<' || str[j] == ' ')
		j++;
	while (str[k + j] != ' ' && str[k + j] != '\0')
		k++;
	*i += (j + k);
	delim = ft_substr(str, j, k);
	if (delim == 0)
		return (1);
	printf("HEREDOC delim = %s\n", delim);
	free(delim);
	return (0);
}

int get_fd_out(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*fd_name;

	j = 0;
	k = 0;
	// printf("...str : %s\n", str);
	while (str[j] == '>' || str[j] == ' ')
		j++;
//	while (str[k] != ' ')
	while (str[k + j] != ' ' && str[k + j] != '\0')
		k++;
	*i += (j + k);
	fd_name = (char *)malloc(sizeof(char) * k + 1);
	if (fd_name == NULL)
		return (1);
	fd_name[k--] = '\0';
	while (k >= 0)
	{
	//	fd_name[k] = str[k];
		fd_name[k] = str[k + j];
		k--;
	}
	//	data->fd_output = open(str, O_RDWR | O_CREAT, 0777);
	data->fd_output = open(fd_name, O_RDWR | O_CREAT, 0777);
	if (data->fd_output == -1)
	{
			free(fd_name);
			return (1);
	}
	free(fd_name);
	return (0);	
}

int get_fd_in(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*fd_name;

	j = 0;
	k = 0;
	while (str[j] == '<' || str[j] == ' ')
		j++;
//	while (str[k] != ' ')
	while (str[k + j] != ' ' && str[k + j] != '\0')
		k++;
	*i += (j + k);
	
	fd_name = (char *)malloc(sizeof(char) * k + 1);
	if (fd_name == NULL)
		return (1);
	fd_name[k--] = '\0';
	while (k >= 0)
	{
		fd_name[k] = str[k + j];
		k--;
	}
	data->fd_input = open(fd_name, O_RDONLY);
	if (data->fd_input == -1)
	{
			free(fd_name);
			return (1);
	}
	free(fd_name);
	
	return (0);	
}

int	redir_out(t_data *data, char *str, int *i)
{
	int	j;
	
	j = 0;
	// printf("^^^str = %s\n", str);
	if (str[j + 1] == '>')
	{
		if (get_fd_out_append(data, str, i))
			return (1);
	}
	else
	{
		if (get_fd_out(data, str, i))
			return (1);
	}
	return (0);
}

int	redir_in(t_data *data, char *str, int *i)
{
	int	j;
	
	j = 0;
	if (str[j + 1] == '<')
	{
		if (get_fd_here_doc(data, str, i))
			return (1);
	}
	else
	{
		if (get_fd_in(data, str, i))
			return (1);
	}
	return (0);
}