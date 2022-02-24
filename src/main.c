/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:12 by rburri            #+#    #+#             */
/*   Updated: 2022/02/24 12:12:24 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int main(int argc, char **argv, char **envp)
{
    char *command_buf;
	t_data data;

	//data.env_paths = find_path(envp);
	//data.cmd_paths = ft_split(data.env_paths, ':');
	
	handle_sigs();
    while(1)
    {
        command_buf = readline("testcli> ");
        if (!(ft_strcmp(command_buf, "exit")))
        	break;
        if (ft_strlen(command_buf) > 0)
            add_history(command_buf);
		if (init_data(&data, envp))
		{
			//error treatment
		}
		if (redirect(&data, command_buf))
		{
			//error treatment
		}
		if (exec_cmd(&data, envp))
		{
			// error treatment
		}
		free(command_buf);
    }
	return (0);
}
