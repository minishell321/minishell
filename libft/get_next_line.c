/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 14:58:08 by rburri            #+#    #+#             */
/*   Updated: 2022/01/22 14:58:59 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	strlen2(char *s)
{
	int	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}

static	char	*join(char *str, char c)
{
	char	*tmp;
	int		i;
	int		len;

	i = 0;
	len = strlen2(str);
	tmp = malloc(len + 2);
	if (tmp == 0)
		return (0);
	while (i < len)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = 0;
	if (str)
		free(str);
	return (tmp);
}

static int	init_check(int fd, t_read *info)
{
	info->fd = fd;
	info->pos = 0;
	info->hasread = read(info->fd, info->data, BUFFER_SIZE);
	if (info->hasread < 0)
		return (0);
	else
		return (1);
}

static char	read_check(t_read *info)
{
	char	result;

	if (info->pos >= info->hasread)
	{
		info->hasread = read(info->fd, info->data, BUFFER_SIZE);
		info->pos = 0;
		if (info->hasread <= 0)
			return (0);
	}
	result = info->data[info->pos];
	info->pos++;
	return (result);
}

char	*get_next_line(int fd)
{
	static t_read	info = {.fd = -1};
	char			c;
	char			*str;

	str = 0;
	if (info.fd != fd)
		if (!init_check(fd, &info))
			return (0);
	c = read_check(&info);
	while (c)
	{
		str = join(str, c);
		if (c == '\n')
			return (str);
		c = read_check(&info);
	}
	return (str);
}
