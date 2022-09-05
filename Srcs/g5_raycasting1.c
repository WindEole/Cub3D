/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g5_raycasting1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:19:04 by iderighe          #+#    #+#             */
/*   Updated: 2022/08/18 18:17:24 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	check_vertical(t_play *play, t_rays *ray)
{
	double	n_tan;

	play->dof = 0;
	n_tan = -tan(ray->ra);
	if (ray->ra == M_PI_2 || ray->ra == 3 * M_PI_2)
	{
		ray->ry = play->py;
		ray->rx = play->px;
		play->dof = play->end_dof;
	}
	else if (ray->ra > (M_PI_2) && ray->ra < (3 * M_PI_2))
	{
		ray->rx = (((int)(play->px) >> 6) << 6) - 0.0001;
		ray->ry = (play->px - ray->rx) * n_tan + play->py;
		ray->xo = -64;
		ray->yo = -ray->xo * n_tan;
	}
	else if (ray->ra < (M_PI_2) || ray->ra > (3 * M_PI_2))
	{
		ray->rx = (((int)(play->px) >> 6) << 6) + 64;
		ray->ry = (play->px - ray->rx) * n_tan + play->py;
		ray->xo = 64;
		ray->yo = -ray->xo * n_tan;
	}
}

void	check_horizontal(t_play *play, t_rays *ray)
{
	double	a_tan;

	play->dof = 0;
	a_tan = -1 / tan(ray->ra);
	if (ray->ra == 0 || ray->ra == M_PI)
	{
		ray->ry = play->py;
		ray->rx = play->px;
		play->dof = play->end_dof;
	}
	else if (ray->ra > M_PI)
	{
		ray->ry = (((int)(play->py) >> 6) << 6) - 0.0001;
		ray->rx = (play->py - ray->ry) * a_tan + play->px;
		ray->yo = -64;
		ray->xo = -ray->yo * a_tan;
	}
	else if (ray->ra < M_PI)
	{
		ray->ry = (((int)(play->py) >> 6) << 6) + 64;
		ray->rx = (play->py - ray->ry) * a_tan + play->px;
		ray->yo = 64;
		ray->xo = -ray->yo * a_tan;
	}
}

void	reset_angle(t_rays *ray)
{
	if (ray->ra < 0)
		ray->ra += 2 * M_PI;
	if (ray->ra > 2 * M_PI)
		ray->ra -= 2 * M_PI;
}

void	raycasting(t_play *play, t_rays *ray, t_data *data)
{
	int	r;

	ray->ra = play->pa - (M_PI / 180 * (FOV / 2));
	reset_angle(ray);
	r = 0;
	while (r < W_WIDTH)
	{
		play->dist_h = 1000000.0;
		play->dist_v = 1000000.0;
		(check_horizontal(play, ray), define_dist(play, ray, data, 0));
		(check_vertical(play, ray), define_dist(play, ray, data, 1));
		define_dist_final(play, ray);
		draw_3d(play, data->rendu, r, data);
		ray->ra += ((M_PI / 180.0) * ((FOV / 1500.0)));
		reset_angle(ray);
		r++;
	}
}
