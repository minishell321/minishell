/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_chk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbotev <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:16:03 by vbotev            #+#    #+#             */
/*   Updated: 2022/02/24 17:56:57 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cnt_quotes(char *command_buf, char c)
{
	char	*first;
	char	*last;
	int		cnt;
	int		flag;

	first = ft_strchr(command_buf, 'c');
	last = ft_strrchr(command_buf, 'c');
	cnt = 0;
	flag = 0;
	if (first)
	{
		cnt++;
		while (first++ != last)
		{
			if (cnt % 2 != 0 && c == '\"' && ft_strchr(command_buf, '$') != 0)
				flag = 1;
			first = ft_strchr(first, 'c');
			cnt++;
		}
		if (cnt % 2 != 0)
			return (1);
		if (cnt % 2 == 0 && flag != 0)
			return (-1);
	}
	return (0);
}


// NOT GENERAL!! - Correction needed so that it detects special chars in all cases when they are outside quotes
int	find_spec_char(char *command_buf)
{
	char	*tmp;

	if (ft_strchr(command_buf, '\\') || ft_strchr(command_buf, ';'))
		if (!ft_strchr(command_buf, '\'') && !ft_strchr(command_buf, '\"'))
			return (1);
	tmp = ft_strchr(command_buf, '\'');
	if (tmp++)
	{
		if (ft_strchr(tmp, '\\') && ft_strchr(tmp, '\\') > ft_strrchr(tmp, '\''))
			return (1);
		if (ft_strchr(tmp, ';') && ft_strchr(tmp, ';') > ft_strrchr(tmp, '\''))
			return (1);
	}
	tmp = ft_strchr(command_buf, '"');
	if (tmp++)
	{
		if (ft_strchr(tmp, '\\') && ft_strchr(tmp, '\\') > ft_strrchr(tmp, '\"'))
			return (1);
		if (ft_strchr(tmp, ';') && ft_strchr(tmp, ';') > ft_strrchr(tmp, '\"'))
			return (1);
	}	
	return (0);
}

int check_command(char *command_buf)
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
		else
			printf("Caution: $ detected between valid open double-quotes\n");
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