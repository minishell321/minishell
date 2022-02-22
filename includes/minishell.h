/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:18 by rburri            #+#    #+#             */
/*   Updated: 2022/02/22 07:34:39 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
//for close, pipe, dup2
# include <fcntl.h>
//for open
# include <stdlib.h>
// for malloc, free, exit
# include <sys/wait.h>
// for waitpid
# include <errno.h>
// for errno
# include <stdio.h>
// for perror
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "../libft/libft.h"


typedef struct s_data
{
	char	*env_paths;
	char	**cmd_paths;
	char	**cmd_args;
	char	*cmd;
}				t_data;

char	*find_path(char **envp);
char	*get_cmd(char **paths, char *cmd);

#endif