/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:18 by rburri            #+#    #+#             */
/*   Updated: 2022/03/03 17:27:43 by vbotev           ###   ########.fr       */
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
// for handling terminal attributes
# include <termios.h>
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
	// pointer to envp PATH no free needed?
	char	**cmd_paths;
	//free by free_env;
	char	*cmd;
	//free in free_data
	int		fd_input;
	// No free needed
	int		fd_output;
	// No free needed
	int		num_of_pipe;
	// No free needed
	int		**pipe_fds;
	//free in free_data
	int		*process_ids;
	//free in free_data
	t_token	*token_stack;
	// free just after cmd_table is created in find_token
	char	***cmd_table;
	//free in free_data
}				t_data;

struct s_token
{
	char	*str;
	int		quotes;
	t_token	*next;
};

int		find_path(t_data *data, char **envp);
int		get_cmd(t_data *data, int i);
int		redirect(t_data *data, char *command_buf);
int		handle_sigs(void);
int		free_data(t_data *data);
int		free_env(t_data *data);
int		exec_cmd(t_data *data, char **envp);
int		check_command(char *command_buf);
int		find_token(t_data *data, char *cmd_str);
void	print_token_stack(t_data *data);
void	free_token_stack(t_data *data);
// pipe_utils
int	pipe_handler(t_data *data, int *i);
int	close_pipe_fds(t_data *data);
// init
int		init_data(t_data *data, char **envp);
int		init_env(t_data *data, char **envp);
int		init_pipe_fds(t_data *data);
int		init_pids_arr(t_data *data);
// redir
int get_fd_out_append(t_data *data, char *str, int *i);
int get_fd_here_doc(t_data *data, char *str, int *i);
int get_fd_out(t_data *data, char *str, int *i);
int get_fd_in(t_data *data, char *str, int *i);
int	redir_out(t_data *data, char *str, int *i);
int	redir_in(t_data *data, char *str, int *i);
// token_utils
int create_token(t_data *data, char *str, int type);
char *send_quoted_string(char *str, int *i);
char *send_unquoted_string(char *str, int *i);

// included in order to make rl_replace_line work
void	rl_replace_line(const char *, int);
//builtins
int	echo(char **argv);
int	builtin_cd(char *str);

#endif
