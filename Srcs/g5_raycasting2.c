/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g5_raycasting2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:02:03 by iderighe          #+#    #+#             */
/*   Updated: 2022/08/19 12:02:06 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

void	define_dist_final(t_play *play, t_rays *ray)
{
	play->dist_final = 0;
	if (play->dist_v < play->dist_h)
	{
		ray->rx = play->dvx;
		ray->ry = play->dvy;
		play->dist_final = play->dist_v;
		if (ray->ra <= M_PI_2 || ray->ra > 3 * M_PI_2)
			play->texture = 'W';
		if (ray->ra > M_PI_2 && ray->ra <= 3 * M_PI_2)
			play->texture = 'E';
	}
	else
	{
		ray->rx = play->dhx;
		ray->ry = play->dhy;
		play->dist_final = play->dist_h;
		if (ray->ra >= 0 && ray->ra < M_PI)
			play->texture = 'S';
		if (ray->ra >= M_PI && ray->ra < 2 * M_PI)
			play->texture = 'N';
	}
}

double	calcul_dist(int px, int py, double rx, double ry)
{
	return (sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py)));
}

void	check_hv(int hv, t_play *play, t_rays *ray)
{
	if (hv == 0)
	{
		play->dhx = ray->rx;
		play->dhy = ray->ry;
		play->dist_h = calcul_dist(play->px, play->py, play->dhx, play->dhy);
	}
	else
	{
		play->dvx = ray->rx;
		play->dvy = ray->ry;
		play->dist_v = calcul_dist(play->px, play->py, play->dvx, play->dvy);
	}
}

void	define_dist(t_play *play, t_rays *ray, t_data *data, int hv)
{
	while (play->dof < play->end_dof)
	{
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * data->map.x + ray->mx;
		if (ray->mp > 0 && ray->mp < data->map.xy && data->mapext[ray->mp] == 1)
		{
			check_hv(hv, play, ray);
			play->dof = play->end_dof;
		}
		else
		{
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			play->dof += 1;
		}
	}
}
