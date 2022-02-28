/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:12 by rburri            #+#    #+#             */
/*   Updated: 2022/02/28 08:46:50 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start_prompt(char **command_buf, t_data *data, char **envp)
{
	 while(1)
    {
        *command_buf = readline("testcli> ");
        if (*command_buf && **command_buf)
		{
            add_history(*command_buf);
			if (!(ft_strcmp(*command_buf, "exit")))
				break;
			if (init_data(data, envp))
			{
				//error treatment
			}
			// if (check_command(*command_buf))
			// {
			// 	//error treatment
			// }
			if (redirect(data, *command_buf))
			{
				//error treatment
			}
			if (exec_cmd(data, envp))
			{
				//error handle
			}
			// pid = fork();
			// if (pid < 0)
			// 	exit(1);
			// if (pid == 0)
			// {
			// 	data.cmd_args = ft_split("ls -l", ' ');
			// 	//data.cmd_args = ft_split(*command_buf, ' ');
			// 	data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
			// 	execve(data.cmd, data.cmd_args, envp);
			// }
			// waitpid(pid, NULL, 0);
			free_data(data);
		}
	if (*command_buf)
		free(*command_buf);
	}
	return (0);
}


int main(int argc, char **argv, char **envp)
{
    char *command_buf;
	t_data data;
	int pid;
	
	command_buf = NULL;
	if (init_env(&data, envp))
	{
		//error handling
	}
	//data.env_paths = find_path(envp);
	//data.cmd_paths = ft_split(data.env_paths, ':');
	handle_sigs();
	start_prompt(&command_buf, &data, envp);
	free_env(&data);
	return (0);
}
