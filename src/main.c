/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:12 by rburri            #+#    #+#             */
/*   Updated: 2022/02/22 17:13:27 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int main(int argc, char **argv, char **envp)
{
    char *command_buf;
	t_data data;
	int pid;

	//data.env_paths = find_path(envp);
	//data.cmd_paths = ft_split(data.env_paths, ':');
	if (init_data(&data, envp))
	{
		//error treatment
	}
	handle_sigs();
    while(1)
    {
        command_buf = readline("testcli> ");
        if (ft_strlen(command_buf) > 0)
            add_history(command_buf);
        if (!(ft_strcmp(command_buf, "exit")))
        	break;
		if (redirect(&data, command_buf))
		{
			//error treatment
		}
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
		{
			data.cmd_args = ft_split("ls -l", ' ');
			//data.cmd_args = ft_split(command_buf, ' ');
			data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
			execve(data.cmd, data.cmd_args, envp);
		}
		waitpid(pid, NULL, 0);
		free(command_buf);
    }
	return (0);
}
