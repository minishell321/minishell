/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:18 by rburri            #+#    #+#             */
/*   Updated: 2022/03/22 08:24:31 by rburri           ###   ########.fr       */
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
	int				type;
	char			*str;
	struct s_token	*args;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_env	*environment;
	char	*command_buf;
	char	*env_paths;
	char	**cmd_paths;
	char	*cmd;
	char	*heredoc_delim;
	char	*heredoc_str;
	char	***heredoc_other_cmds;
	int		heredoc_ign_tab;
	int		fd_input;
	int		fd_output;
	int		num_of_pipe;
	int		**pipe_fds;
	int		*process_ids;
	int		exit_code;
	t_token	*token_stack;
	char	***cmd_table;
}	t_data;

int		local_env(t_data *data, char **envp);
int		create_env_entry(t_data *data, char *value, char *variable);
int		cnt_var(t_data *data);
int		identify_env(t_data *data, char *cmd);
void	update_pwd(t_data *data, char *cwd);
int		cpy_env(t_data *data, char **cpy_env_variables);
void	sort_env(char **cpy);
int		find_path(t_data *data);
int		get_cmd(t_data *data, int i);
int		get_cmd_hd(t_data *data, int i);
int		redirect(t_data *data, char *command_buf);
int		handle_sigs(void);
int		handle_sigs_child(void);
int		check_command(char *command_buf);
int		find_token(t_data *data, char *cmd_str);
//exec_cmd
int		exec_cmd(t_data *data, char **envp);
int		exec_cmd_hd(t_data *data, char **envp);
int		redir_handler(t_data *data, int i);
int		wait_all_children(t_data *data);
// Free_all
int		free_env(t_data *data);
int		free_data(t_data *data);
void	free_token_stack(t_data *data);
void	free_heredoc(t_data *data);
// pipe_utils
int		pipe_handler(t_data *data, int i);
int		close_pipe_fds(t_data *data);
// init
int		init_data(t_data *data);
int		init_env(t_data *data, char **envp);
int		init_pipe_fds(t_data *data);
int		init_pids_arr(t_data *data);
// redir
int		redir(t_data *data, char *str, int *i);
int		get_fd_out_append(t_data *data, char *str, int *i);
int		get_here_doc(t_data *data, char *str, int *i);
int		get_fd_out(t_data *data, char *str, int *i);
int		get_fd_in(t_data *data, char *str, int *i);
// token_utils
int		create_token(t_data *data, char *str, int *type);
char	*send_quoted_str(char *str, int *i);
char	*send_unquoted_str(char *str, int *i);
void	print_token(t_data *data);
// token_handler
int		token_handler(t_data *data);
// cmd_table
int		cmd_table(t_data *data);
// included in order to make rl_replace_line work
void	rl_replace_line(const char *var1, int var2);
// replace_var_env
char	*find_dollars(char *command_buf, t_data *data);
//builtins
void	update_pwd(t_data *data, char *cwd);
void	close_fds(t_data *data);
int		check_if_builtin(t_data *data);
int		exec_if_builtin(t_data *data);
int		builtin_echo(char **argv, int fd_output);
int		builtin_cd(t_data *data);
int		builtin_pwd(int fd_output);
int		builtin_env(t_data *data);
int		builtin_export(t_data *data);
int		builtin_unset(t_data *data);
int		check_exit(t_data *data);
//HEREDOC
int		heredoc_handler(t_data *data, char **envp);
int		check_is_heredoc(char *cmd_buf);
int		token_handler_heredoc(t_data *data);
int		cmd_table_heredoc(t_data *data);
#endif
