/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoinus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:49:46 by acoinus           #+#    #+#             */
/*   Updated: 2022/08/29 15:59:32 by acoinus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_spaces(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && (s[i] == ' ' || (s[i] > 8 && s[i] <= 13)))
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	sign;
	long	n;

	sign = 1;
	n = 0;
	i = ft_spaces(str);
	if (str[i] && (str[i] == '-' || str[i] == '+'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		n = n * 10 + str[i] - '0';
		if (n > 2147483647 && sign == 1)
			return (-1);
		if (n > 2147483648 && sign == -1)
			return (0);
		i++;
	}
	return (sign * n);
}
