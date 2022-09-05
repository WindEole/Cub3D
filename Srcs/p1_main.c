/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p1_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoinus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:39:06 by acoinus           #+#    #+#             */
/*   Updated: 2022/09/01 18:10:48 by acoinus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	ft_free(t_data *data, int ret)
{
	int	i;

	if (data->s_cub)
		free(data->s_cub);
	if (data->mapext)
		free(data->mapext);
	if (data->tex_switch)
	{
		i = -1;
		while (++i < 4)
			if (data->tx[i])
				free(data->txtr[i]);
	}
	return (ret);
}

static void	init(t_data *data, int i)
{
	data->fd = 0;
	data->mapext = NULL;
	data->tex_switch = 0;
	while (++i < 4)
		data->txtr[i] = NULL;
	data->txtr[4] = "\0";
	i = -1;
	while (++i < 4)
		data->tx[i] = 0;
	data->f = 0;
	data->c = 0;
}

int	main(int ac, char **av)
{
	t_data	data;

	init(&data, -1);
	if (ac != 2)
		return (ft_error(0, -1));
	data.s_cub = ft_strdup(av[1]);
	if (pars(&data))
		return (ft_free(&data, 1));
	if (graphical(&data))
		return (ft_free(&data, 1));
	return (ft_free(&data, 0));
}
