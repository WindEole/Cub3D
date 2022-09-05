/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:25:30 by iderighe          #+#    #+#             */
/*   Updated: 2022/02/05 18:58:24 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	ln;
	int			a;

	ln = n;
	if (ln < 0)
	{
		write(fd, "-", 1);
		ln = ln * -1;
	}
	if (ln >= 0)
	{
		a = ln % 10 + 48;
		ln = ln / 10;
		if (ln > 0)
			ft_putnbr_fd(ln, fd);
		write(fd, &a, 1);
	}
}
