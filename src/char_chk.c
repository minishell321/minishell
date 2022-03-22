/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_chk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:16:03 by vbotev            #+#    #+#             */
/*   Updated: 2022/03/22 09:49:22 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_return(int cnt, int flag)
{
	if (cnt % 2 != 0)
		return (1);
	else if (cnt % 2 == 0 && flag != 0)
		return (-1);
	else
		return (0);
}

int	cnt_quotes(char *command_buf, char c)
{
	char	*first;
	char	*last;
	char	*cpy;
	int		cnt;
	int		flag;

	cnt = 0;
	flag = 0;
	if (ft_strchr(command_buf, c))
	{
		first = ft_strdup(ft_strchr(command_buf, c));
		cpy = first;
		last = ft_strrchr(first, c);
		cnt++;
		while (first++ != last)
		{
			if (cnt % 2 != 0 && c == '\"' && ft_strchr(first, '$') != 0)
				flag = 1;
			first = ft_strchr(first, c);
			cnt++;
		}
		free(cpy);
	}
	return (check_return(cnt, flag));
}

// NOT GENERAL!! - Correction needed so that it detects special chars in all
// cases when they are outside quotes
int	find_spec_char(char *command_buf)
{
	char	*s;

	if (ft_strchr(command_buf, '\\') || ft_strchr(command_buf, ';'))
		if (!ft_strchr(command_buf, '\'') && !ft_strchr(command_buf, '\"'))
			return (1);
	if (ft_strchr(command_buf, '\''))
	{
		s = ft_strchr(command_buf, '\'') + 1;
		if ((ft_strchr(s, '\\') && ft_strchr(s, '\\') > ft_strrchr(s, '\''))
			|| (ft_strchr(s, ';') && ft_strchr(s, ';') > ft_strrchr(s, '\'')))
		{
			return (1);
		}
	}
	if (ft_strchr(command_buf, '\"'))
	{
		s = ft_strchr(command_buf, '\"') + 1;
		if ((ft_strchr(s, '\\') && ft_strchr(s, '\\') > ft_strrchr(s, '\"'))
			|| (ft_strchr(s, ';') && ft_strchr(s, ';') > ft_strrchr(s, '\"')))
		{
			return (1);
		}
	}	
	return (0);
}

int	check_command(char *command_buf)
{
	int	ret;

	ret = cnt_quotes(command_buf, '\"');
	if (ret != 0)
	{
		if (ret == 1)
		{
			printf("Error: Odd number of double-quotes found\n");
			return (1);
		}
	}
	if (cnt_quotes(command_buf, '\''))
	{
		printf("Error: Odd number of single-quotes found\n");
		return (1);
	}
	if (find_spec_char(command_buf))
	{
		printf("Error: Special charater detected outside of quotes\n");
		return (1);
	}
	return (0);
}
