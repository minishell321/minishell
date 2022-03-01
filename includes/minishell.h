/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:18 by rburri            #+#    #+#             */
/*   Updated: 2022/03/01 12:41:38 by rburri           ###   ########.fr       */
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

# define CMD 1
# define ARG 2

typedef struct s_token
{
	int type;
	char	*str;
	struct s_token *args;
	struct s_token	*next;
}				t_token;

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
	t_token	*cmds;
}				t_data;

int		find_path(t_data *data, char **envp);
int		get_cmd(t_data *data);
int		redirect(t_data *data, char *command_buf);
int		init_data(t_data *data, char **envp);
int		init_env(t_data *data, char **envp);
int		handle_sigs(void);
int		free_data(t_data *data);
int		free_env(t_data *data);
int		exec_cmd(t_data *data, char **envp);
int		check_command(char *command_buf);
int		find_token(t_data *data, char *cmd_str);
void	print_token_stack(t_data *data);

// included in order to make rl_replace_line work
void	rl_replace_line(const char *, int);

#endif
