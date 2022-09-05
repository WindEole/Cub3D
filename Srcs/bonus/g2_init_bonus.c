/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g2_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:58:20 by iderighe          #+#    #+#             */
/*   Updated: 2022/08/18 17:58:27 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	init_texture(t_data *data, int s)
{
	int	fd;

	data->tex.fl = NULL;
	data->tex.ce = NULL;
	data->tex.f = "./Tex/F.xpm";
	fd = open(data->tex.f, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	data->tex.c = "./Tex/C.xpm";
	fd = open(data->tex.c, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	data->tex.no = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[0], &s, &s);
	data->tex.so = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[1], &s, &s);
	data->tex.ea = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[2], &s, &s);
	data->tex.we = mlx_xpm_file_to_image(data->mlx_ptr, data->txtr[3], &s, &s);
	data->tex.fl = mlx_xpm_file_to_image(data->mlx_ptr, data->tex.f, &s, &s);
	data->tex.ce = mlx_xpm_file_to_image(data->mlx_ptr, data->tex.c, &s, &s);
	if (data->tex.no == NULL || data->tex.so == NULL || data->tex.ea == NULL
		|| data->tex.we == NULL)
		return (1);
	return (0);
}

void	init_player(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.xy)
	{
		if (ft_strchr(data->mapext[i], "NSEW"))
		{
			data->play.py = (i / data->map.x * CUBE_SIDE);
			data->play.px = ((i - data->play.py * data->map.x / CUBE_SIDE)
					* CUBE_SIDE);
			data->play.px += CUBE_SIDE / 2;
			data->play.py += CUBE_SIDE / 2;
			data->play.pos_init = i;
			if (data->mapext[i] == 'N')
				data->play.pa = 3 * M_PI_2;
			if (data->mapext[i] == 'S')
				data->play.pa = M_PI_2;
			if (data->mapext[i] == 'E')
				data->play.pa = 0;
			if (data->mapext[i] == 'W')
				data->play.pa = M_PI;
			return ;
		}
		i++;
	}
}

void	init_key(t_data *data)
{
	data->key.w = 0;
	data->key.a = 0;
	data->key.s = 0;
	data->key.d = 0;
	data->key.l = 0;
	data->key.r = 0;
	data->tex.no = NULL;
	data->tex.so = NULL;
	data->tex.ea = NULL;
	data->tex.we = NULL;
	data->rendu = NULL;
	if (data->f == -1)
		data->f = BLACK_PIXEL;
	if (data->c == -1)
		data->c = BLACK_PIXEL;
}

void	init_data(t_data *data)
{
	init_key(data);
	data->map.xy = data->map.x * data->map.y;
	if (data->map.x > data->map.y)
		data->play.end_dof = data->map.x;
	else
		data->play.end_dof = data->map.y;
	data->map.len_x = data->map.x * CUBE_SIDE;
	data->map.len_y = data->map.y * CUBE_SIDE;
	if (data->map.len_x > W_WIDTH * 2 / 3 || data->map.len_y > W_HEIGHT * 2 / 3)
		data->scale = 0.3;
	else
		data->scale = 0.5;
	data->play.width = 3;
	data->play.height = 3;
	init_player(data);
	data->play.pdx = cos(data->play.pa) * 5;
	data->play.pdy = sin(data->play.pa) * 5;
	data->play.dhx = data->play.px;
	data->play.dhy = data->play.py;
	data->play.dvx = data->play.px;
	data->play.dvy = data->play.py;
}
