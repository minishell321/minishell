/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:12 by rburri            #+#    #+#             */
/*   Updated: 2022/03/05 13:33:16 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	start_prompt(char *command_buf, t_data *data, char **envp)
{
	int pid;

	 while(1)
    {
        command_buf = readline("testcli> ");
		if (command_buf == 0)
		{
			printf("exit\n");
			break;
		}
        if (command_buf && *command_buf)
		{
            add_history(command_buf);
			if ((ft_strncmp(command_buf, "exit", 4)) == 0)
				break;
			init_data(data, envp);
			if (check_command(command_buf))
			 	continue;
			if (find_token(data, command_buf))
			{
				printf("error find token\n");
				continue;
			}
			if (token_handler(data))
				continue;
			if (exec_cmd(data, envp))
				continue;
			//  pid = fork();
			//  if (pid < 0)
			//  	exit(1);
			//  if (pid == 0)
			//  {
			//  //	data.cmd_args = ft_split("ls -l", ' ');
			//  	data->cmd_args = ft_split(command_buf, ' ');
			//  //	data->cmd = get_cmd(data->cmd_paths, data->cmd_args[0]);
			//  	get_cmd(data);
			//  	execve(data->cmd, data->cmd_args, envp);
			//  }
			//  waitpid(pid, NULL, 0);
			if (data)
				free_data(data);
		}
		if (command_buf)
			free(command_buf);
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
	handle_sigs();
	start_prompt(command_buf, &data, envp);
	free_env(&data);
	return (0);
}
