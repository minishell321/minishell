/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 10:46:34 by rburri            #+#    #+#             */
/*   Updated: 2022/03/16 08:49:12 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_fd_out_append(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*fd_name;

	j = 0;
	k = 0;
	while (str[j] == '>' || str[j] == ' ')
		j++;
	while (str[k + j] != ' ' && str[k + j] != '\0')
		k++;
	*i += (j + k);
	fd_name = ft_substr(str, j, k);
	if (fd_name == NULL)
		return (1);
	data->fd_output = open(fd_name, O_RDWR | O_APPEND, 0777);
	if (data->fd_output == -1)
	{
		perror("redir");
		free(fd_name);
		return (1);
	}
	free(fd_name);
	return (0);
}

int	get_here_doc(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
//	char	*delim;

	j = 0;
	k = 0;
	//the if data is only here to shut Werror, to delete 
//	if (data)
//	{
		while (str[j] == '<' || str[j] == ' ')
			j++;
		while (str[k + j] != ' ' && str[k + j] != '\0')
			k++;
		*i += (j + k);
		data->heredoc_delim = ft_substr(str, j, k);
		if (data->heredoc_delim == 0)
			return (1);
		printf("HEREDOC delim = %s\n", data->heredoc_delim);
		// data->heredoc = 1;
	//	free(delim);
//	}
	return (0);
}

int	get_fd_out(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*fd_name;

	j = 0;
	k = 0;
	while (str[j] == '>' || str[j] == ' ')
		j++;
	while (str[k + j] != ' ' && str[k + j] != '\0')
		k++;
	*i += (j + k);
	fd_name = ft_substr(str, j, k);
	if (fd_name == NULL)
		return (1);
	data->fd_output = open(fd_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data->fd_output == -1)
	{
		perror("redir");
		free(fd_name);
		return (1);
	}
	free(fd_name);
	return (0);
}

int	get_fd_in(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*fd_name;

	j = 0;
	k = 0;
	while (str[j] == '<' || str[j] == ' ')
		j++;
	while (str[k + j] != ' ' && str[k + j] != '\0')
		k++;
	*i += (j + k);
	fd_name = ft_substr(str, j, k);
	if (fd_name == NULL)
		return (1);
	data->fd_input = open(fd_name, O_RDONLY);
	if (data->fd_input == -1)
	{
		perror("redir");
		free(fd_name);
		return (1);
	}
	free(fd_name);
	return (0);
}
