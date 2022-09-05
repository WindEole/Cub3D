/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g7_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:18:24 by iderighe          #+#    #+#             */
/*   Updated: 2022/08/18 18:18:27 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	draw_ray_0(t_data *data, double a, double dist, int color)
{
	int		i;
	double	px;
	double	py;

	i = 0;
	while (++i < 100)
	{
		px = (data->play.px + (cos(a) * i * (dist / 100))) * data->scale;
		py = (data->play.py + (sin(a) * i * (dist / 100))) * data->scale;
		if (px < data->map.len_x && py < data->map.len_y)
			my_pixel_put(data->rendu, px + 15, py + 15, color);
	}
}

int	render_player(t_img *img, t_play play, t_data *data)
{
	int	i;
	int	j;
	int	py_scale;
	int	px_scale;

	py_scale = play.py * data->scale;
	px_scale = play.px * data->scale;
	i = py_scale - play.height;
	while (i < py_scale + play.height)
	{
		j = px_scale - play.width;
		while (j < px_scale + play.width)
		{
			my_pixel_put(img, j + 15, i + 15, RED_PIXEL);
			j++;
		}
		++i;
	}
	draw_ray_0(data, play.pa, 30.0, RED_PIXEL);
	return (0);
}

int	fill_minimap(t_data *data, int x, int y, int color)
{
	int	begin_x;
	int	begin_y;
	int	i;
	int	j;

	begin_x = x * CUBE_SIDE * data->scale;
	begin_y = y * CUBE_SIDE * data->scale;
	j = begin_y;
	while (j < begin_y + CUBE_SIDE * data->scale)
	{
		i = begin_x;
		while (i < begin_x + CUBE_SIDE * data->scale)
		{
			if (i == begin_x + (CUBE_SIDE * data->scale) - 1
				|| j == begin_y + (CUBE_SIDE * data->scale) - 1)
				my_pixel_put(data->rendu, i + 15, j + 15, BLACK_PIXEL);
			else
				my_pixel_put(data->rendu, i + 15, j + 15, color);
			i += 2;
		}
		j += 2;
	}
	return (0);
}

int	render_map(t_map map, t_data *data)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < map.y)
	{
		x = 0;
		while (x < map.x)
		{
			i = y * map.x + x;
			if (data->mapext[i] == 1)
				fill_minimap(data, x, y, WHITE_PIXEL);
			else if (data->mapext[i] == 0 || ft_strchr(data->mapext[i], "NSEW"))
				fill_minimap(data, x, y, GRAY_PIXEL);
			x++;
		}
		y++;
	}
	return (0);
}
