/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p5_wall_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoinus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 13:52:26 by acoinus           #+#    #+#             */
/*   Updated: 2022/08/30 18:24:01 by acoinus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

static int	wall_checker(t_data *data, int *s, int sz, int x)
{
	int	i;

	i = -1;
	while (++i < sz && data->mapext)
		if ((i < x || !((i + 1) % x) || !((i + 1) % x - 1) || i > sz - x)
			&& s[i] == 0)
			return (ft_error(5, data->fd));
	i = 0;
	while (i < sz && data->mapext)
	{
		if (data->mapext[i] == 0)
			if (s[i - x - 1] == 32 || s[i - x] == 32 || s[i - x + 1] == 32
				|| s[i - 1] == 32 || s[i + 1] == 32 || s[i + x - 1] == 32
				|| s[i + x] == 32 || s[i + x + 1] == 32)
				return (ft_error(5, data->fd));
		i++;
	}
	return (0);
}

int	p_checker(t_data *data, int i)
{
	int	sz;
	int	p;

	p = 0;
	sz = data->map.y * data->map.x;
	while (++i < sz && data->mapext)
	{
		if (data->mapext[i] != 'N' && data->mapext[i] != 'S'
			&& data->mapext[i] != 'E' && data->mapext[i] != 'W'
			&& data->mapext[i] != 1 && data->mapext[i] != 0
			&& data->mapext[i] != 32)
			return (ft_error(5, data->fd));
		if (data->mapext[i] == 'N' || data->mapext[i] == 'S'
			|| data->mapext[i] == 'E' || data->mapext[i] == 'W')
			p++;
	}
	if (p != 1)
		return (ft_error(5, data->fd));
	return (wall_checker(data, data->mapext, sz, data->map.x));
}
