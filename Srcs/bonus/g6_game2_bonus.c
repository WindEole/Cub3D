/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g6_game2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:04:12 by iderighe          #+#    #+#             */
/*   Updated: 2022/08/31 14:04:14 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	find(float x, float y, t_img *tex)
{
	x = x * tex->width;
	y = y * tex->height;
	return (((int *)tex->data)[(int)y * tex->width + (int)x]);
}

int	shading(int c, t_data *data, int end_line, float pow)
{
	int		r;
	int		g;
	int		b;

	r = (c & (0xFF << 16)) >> 16;
	g = (c & (0xFF << 8)) >> 8;
	b = (c & 0xFF);
	if (end_line > 0)
	{
		pow = fabs((W_HEIGHT / 2.0) - end_line) / (W_HEIGHT / 2.0);
		r *= pow;
		g *= pow;
		b *= pow;
	}
	else
	{
		pow = 0.5 * data->play.dist_final / CUBE_SIDE;
		if (pow > 1)
		{
			r /= pow;
			g /= pow;
			b /= pow;
		}
	}
	return ((r << 16) + (g << 8) + b);
}

void	draw_floor_ceiling(t_data *data, t_img *img, int line_end, int r)
{
	int		coef;
	double	d;
	int		c;

	coef = (int)((W_WIDTH * 0.5) / tan(FOV * 0.5 * M_PI / 180));
	while (line_end <= img->height)
	{
		d = (coef / (line_end - (W_HEIGHT / 2.0)))
			/ (1.155 * cos(fabs(data->play.pa - data->play.ray.ra)));
		data->tex.tx = (int)(data->play.px * (data->tex.fl->width / CUBE_SIDE)
				+ (cos(data->play.ray.ra) * d * data->tex.fl->width * 0.5));
		data->tex.ty = (int)(data->play.py * (data->tex.fl->height / CUBE_SIDE)
				+ (sin(data->play.ray.ra) * d * data->tex.fl->height * 0.5));
		c = define_color('F', &data->tex);
		c = shading(c, data, line_end, 0.0);
		my_pixel_put(img, r, line_end, c);
		data->tex.tx = (int)(data->play.px * (data->tex.ce->width / CUBE_SIDE)
				+ (cos(data->play.ray.ra) * d * data->tex.ce->width * 0.5));
		data->tex.ty = (int)(data->play.py * (data->tex.ce->height / CUBE_SIDE)
				+ (sin(data->play.ray.ra) * d * data->tex.ce->height * 0.5));
		c = define_color('C', &data->tex);
		c = shading(c, data, line_end, 0.0);
		my_pixel_put(img, r, W_HEIGHT - line_end, c);
		line_end++;
	}
}
