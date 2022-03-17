/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 10:40:55 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/17 08:13:39 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	heredoc_handler(t_data *data, char **envp)
// {
// 	char	*delim;
// 	char	*str;
// 	char	*tmp;
// 	int		i;
	
// 	i = 0;
// 	// printf("HERE - heredoc_delim: %s\n", data->heredoc_delim);
// 	delim = data->heredoc_delim;
// 	str = data->command_buf;
// 	if (data->heredoc_str == 0)
// 	{
// 		data->heredoc_str = malloc(sizeof(char));
// 		if (data->heredoc_str == 0)
// 			return (1);
// 		data->heredoc_str[0] = 0;
// 	}
// //	if (ft_strchr(delim, '\'') || ft_strchr(delim, '\"'))
// //	{
// 	//	printf("PRIOR TO STRNCMP\n");
// 		if (ft_strncmp(str, delim, ft_strlen(str))
// 			&& ft_strlen(str) != ft_strlen(delim))
// 		{
// 			tmp = data->heredoc_str;
// 			data->heredoc_str = ft_strjoin(tmp, "\n");
// 			free (tmp);
// 			tmp = data->heredoc_str;
// 			data->heredoc_str = ft_strjoin(tmp, str);
// 			free (tmp);
// 	//		printf("THE STRING IS: %s\n", data->heredoc_str);
// 		}
// 		else
// 		{
// 			tmp = data->heredoc_str;
// 			data->heredoc_str = ft_strjoin(tmp, "\n");
// 			free (tmp);
// 			// if (!ft_strncmp(data->heredoc_other_cmds[0][0], "", 1))
// 			// if has no heredoc_other_cmds, do nothing, free everything heredoc related

// 			//else
// 			data->num_of_pipe += 1;
// 			init_pids_arr(data);
// 			init_pipe_fds(data);
// 			exec_cmd(data, envp);
// 			ft_putstr_fd(data->heredoc_str, data->fd_output);
			
// 			free (data->heredoc_str);
// 			data->heredoc_str = 0;
// 			printf("***HEREDOC END\n");
// 			while (data->heredoc_other_cmds[0][i] != 0)
// 			{
// 				printf("heredoc_other_cmds[0][%d]: %s\n", i, data->heredoc_other_cmds[0][i]);
// 				i++;
// 			}
// 			free(data->heredoc_delim);
// 			data->heredoc_delim = 0;
// 			data->heredoc = 0;
// 		}
// //	}
// 	return (0);
// }

static int	malloc_heredoc_str(t_data *data)
{
	data->heredoc_str = malloc(sizeof(char));
	if (data->heredoc_str == 0)
		return (1);
	data->heredoc_str[0] = 0;
	return (0);
}

static void	check_if_must_send(t_data *data, char **envp)
{
	if (ft_strncmp(data->heredoc_other_cmds[1][0], "", 1) == 0)
		free_heredoc(data);
	else
	{
		data->heredoc_other_cmds[0][2] = data->heredoc_str;
		data->num_of_pipe += 1;
		init_pids_arr(data);
		init_pipe_fds(data);
		exec_cmd_hd(data, envp);
		free_heredoc(data);
	}
}

int	heredoc_handler(t_data *data, char **envp)
{
	char	*str;
	char	*tmp;
	char	*str_endl;

	str = NULL;
	str = readline("> ");
	if (malloc_heredoc_str(data))
		return (1);
	while (ft_strncmp(str, data->heredoc_delim, ft_strlen(str)))
	{
		str_endl = ft_strjoin(str, "\n");
		free(str);
		tmp = ft_strdup(data->heredoc_str);
		free(data->heredoc_str);
		data->heredoc_str = ft_strjoin(tmp, str_endl);
		free (str_endl);
		free (tmp);
		str = readline("> ");
	}
	free(str);
	check_if_must_send(data, envp);
	return (0);
}

int	check_is_heredoc(char *cmd_buf)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (cmd_buf[i])
	{
		if (cmd_buf[i] == '\"')
			d_quote++;
		if (cmd_buf[i] == '\'')
			s_quote++;
		if (cmd_buf[i] == '<' && cmd_buf[i + 1] == '<'
			&& s_quote % 2 == 0 && d_quote % 2 == 0)
			return (1);
		i++;
	}
	return (0);
}
