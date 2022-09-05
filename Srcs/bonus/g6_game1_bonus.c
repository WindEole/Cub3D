/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g6_game1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 15:35:36 by iderighe          #+#    #+#             */
/*   Updated: 2022/08/18 18:18:05 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	define_color(char t, t_tex *tex)
{
	int	c;

	if (t == 'W')
		c = find(tex->tx, tex->ty, tex->we);
	if (t == 'E')
		c = find(tex->tx, tex->ty, tex->ea);
	if (t == 'S')
		c = find(tex->tx, tex->ty, tex->so);
	if (t == 'N')
		c = find(tex->tx, tex->ty, tex->no);
	if (t == 'F')
		c = ((int *)tex->fl->data)[((int)(tex->ty) &(tex->fl->height - 1))
			* tex->fl->width + ((int)(tex->tx) &(tex->fl->width - 1))];
	if (t == 'C')
		c = ((int *)tex->ce->data)[((int)(tex->ty) &(tex->ce->height - 1))
			* tex->ce->width + ((int)(tex->tx) &(tex->ce->width - 1))];
	return (c);
}

void	define_tx(t_data *data, t_play *play)
{
	if (play->texture == 'S' || play->texture == 'N')
	{
		data->tex.tx = ((play->ray.rx / CUBE_SIDE)
				- (int)((play->ray.rx / CUBE_SIDE)));
		if (play->ray.ra < M_PI)
			data->tex.tx = 1 - data->tex.tx;
	}
	else if (play->texture == 'E' || play->texture == 'W')
	{
		data->tex.tx = (play->ray.ry / CUBE_SIDE)
			- (int)((play->ray.ry / CUBE_SIDE));
		if (play->ray.ra > M_PI_2 && play->ray.ra < 3 * M_PI_2)
			data->tex.tx = 1 - data->tex.tx;
	}
}

void	fish_eye(t_play *play)
{
	float	fish_eye;

	fish_eye = play->pa - play->ray.ra + M_PI;
	if (fish_eye < 0)
		fish_eye += 2 * M_PI;
	if (fish_eye > 2 * M_PI)
		fish_eye -= 2 * M_PI;
	play->dist_final = fabs(play->dist_final * cos(fish_eye));
}

void	draw_3d(t_play *play, t_img *img, int r, t_data *data)
{
	int		line_h;
	int		line_origin;
	int		line_end;
	int		c;

	fish_eye(play);
	line_h = CUBE_SIDE * img->height / play->dist_final;
	line_origin = (img->height / 2) - (line_h / 2);
	data->tex.ty_off = line_origin;
	line_end = line_h + line_origin;
	if (line_origin < 0)
		line_origin = 0;
	define_tx(data, play);
	while (line_origin < line_end && line_origin < img->height)
	{
		data->tex.ty = (line_origin - data->tex.ty_off) / line_h;
		c = define_color(play->texture, &data->tex);
		c = shading(c, data, -1, 0);
		my_pixel_put(img, r, line_origin, c);
		++line_origin;
	}
	draw_floor_ceiling(data, img, line_end, r);
}

void	render_background(t_img *rendu, int c, int f)
{
	int	i;
	int	j;

	i = 0;
	while (i < rendu->height / 2)
	{
		j = 0;
		while (j < rendu->width)
			my_pixel_put(rendu, j++, i, c);
		++i;
	}
	i = rendu->height / 2;
	while (i < rendu->height)
	{
		j = 0;
		while (j < rendu->width)
			my_pixel_put(rendu, j++, i, f);
		++i;
	}
}
