/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:18 by rburri            #+#    #+#             */
/*   Updated: 2022/02/24 09:10:32 by rburri           ###   ########.fr       */
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
# include <signal.h>
// to handle signals
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
	int		fd_input;
	int		fd_output;
	int		num_of_pipe;
	int		**pipe_fds;
	int		*process_ids; 
	char 	**cmds;
}				t_data;

char	*find_path(char **envp);
char	*get_cmd(char **paths, char *cmd);
int		redirect(t_data *data, char *command_buf);
int		init_data(t_data *data, char ** envp);
int		handle_sigs(void);
int		free_all(t_data *data);
int		exec_cmd(t_data *data, char **envp);

#endif
