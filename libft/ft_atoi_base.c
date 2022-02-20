/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 08:58:38 by rburri            #+#    #+#             */
/*   Updated: 2022/01/07 09:29:10 by rburri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid(int c, int baselen)
{
	if (ft_isdigit(c))
		return (c - '0' < baselen);
	if (ft_islower(c))
		return (c - 'a' + 10 < baselen);
	if (ft_isupper(c))
		return (c - 'A' + 10 < baselen);
	return (0);
}

static int	get_value(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	if (ft_islower(c))
		return (c - 'a' + 10);
	return (c - 'A' + 10);
}

int	ft_atoi_base(const char *str, int base)
{
	int	sum;
	int	i;
	int	sign;

	if (str == NULL || !*str)
		return (0);
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	sum = 0;
	while (is_valid(str[i], base))
	{
		sum *= base;
		sum += get_value(str[i]);
		i++;
	}
	return (sign * sum);
}
