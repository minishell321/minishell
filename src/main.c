/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 07:42:12 by rburri            #+#    #+#             */
/*   Updated: 2022/02/21 07:52:23 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int main()
{
    char *command_buf;
    int res;

    while(1)
    {
        command_buf = readline("testcli> ");
        if (ft_strlen(command_buf) > 0)
            add_history(command_buf);
        if (!(res = ft_strcmp(command_buf, "exit")))
        	break;
    }
}
