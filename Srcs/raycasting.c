/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 16:03:44 by iderighe          #+#    #+#             */
/*   Updated: 2022/07/20 16:03:50 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_pixel_put(t_ig *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_ig *img, int c, int f)
{
	int	i;
	int	j;

	i = 0;
	while (i < W_HEIGHT / 2)//(i < 320 / 2)
	{
		j = 530;
		while (j < W_WIDTH)
			my_pixel_put(img, j++, i, c);
		++i;
	}
	i = W_HEIGHT / 2;//i = 320 / 2;
	while (i < W_HEIGHT)//(i < 320)
	{
		j = 530;
		while (j < W_WIDTH)
			my_pixel_put(img, j++, i, f);
		++i;
	}
}

// void draw_line(t_ig *img, t_play play)
// {
// 	int	i;
// 	int j;

// 	play.line.a = ((play.py - play.pdy)/(play.px - play.pdx));
// 	play.line.b = ((play.pdy * (play.px - play.pdx)) - (play.pdx * (play.py-play.pdy))) / (play.px - play.pdx);
// printf(GREEN"px = [%d] | py = [%d] | pdx = [%f] | pdy = [%f]"RESET"\n", play.px, play.py, play.pdx, play.pdy);	
// printf(RED"a = [%f] | b = [%f]"RESET"\n", play.line.a, play.line.b);
// 	i = play.py;
// 	while (i < play.py + play.pdy * 5)
// 	{
// 		j = play.px;
// 		while (j < play.px + play.pdx * 5)
// 		{
// 		printf(BLUE"ici ?"RESET"\n");
// 			if (i == play.line.a * j + play.line.b)
// 				my_pixel_put(img, j, i, GREEN_PIXEL);
// 			j++;			
// 		}
// 		++i;
// 	}
// }

// void draw_ray_on_minimap(t_ig *img, t_play *play, t_rays *ray)//, t_line line)
// {
// 	int	i;
// 	int j;

// //	i = line.yA;
// 	i = play->py;
// 	while (i < ray->ry)
// 	{
// 		j = play->px;
// 		while (j < line.xB)
// 		{
// 			if (i == line.a * j + line.b)
// 				my_pixel_put(img, j, i, line.color);
// 			j++;			
// 		}
// 		++i;
// 	}
// }

void draw_ray_0(t_ig *img, t_play *play, double a, double dist, int color)
{
	int i;
	double px;
	double py;

	i = 0;
	while (++i < 100)
	{
		px = play->px + (cos(a) * i * (dist/100));
		py = play->py + (sin(a) * i * (dist/100));
		if (px < 1500 && py < 1500)
			my_pixel_put(img, px, py, color);
	}
}

void	draw_3d(t_play *play, t_map *map, t_ig *img, int r)
{
	int		i;
//	int		j;
	float	line_origin;
	float	fish_eye;
	float	line_h;

	fish_eye = play->pa - play->ray.ra + M_PI;
	if (fish_eye < 0)
		fish_eye += 2 * M_PI;
	if (fish_eye > 2 * M_PI)
		fish_eye -= 2 * M_PI;
	play->dist_final = play->dist_final * cos(fish_eye);
	line_h = map->cube_aire * W_HEIGHT / play->dist_final;
	if (line_h > W_HEIGHT)
		line_h = W_HEIGHT;
	line_origin = (W_HEIGHT / 2) - line_h / 2;
	i = line_origin;
	while (i < line_h + line_origin)
	{
	//	j = r;// + 530;
		//while (j < (r + 530))//(j < (r * 8 + 530) + 8)
		my_pixel_put(img, r, i, play->ray.ray_color);
		++i;
	}
}

void	draw_points(t_data *data, t_play *play, t_map *map, int color)
{
	int	a;
	int	b;

	a = play->ray.ry + play->height;// On affiche le point de contact du rayon
	while (a > play->ray.ry && a < map->len_mapYS)
	{
		b = play->ray.rx;
//printf(RED"rx = %f || ry = %f || len_y = %d || len_x = %d "RESET"\n", play->ray.rx, play->ray.ry, map->len_mapYS, map->len_mapXS);
		while (b < play->ray.rx + play->width && b < map->len_mapXS)
			my_pixel_put(&data->minimap, b++, a, color);
		--a;
	}
}

void	define_dist_final(t_play *play, t_rays *ray)
{
	if (play->dist_V < play->dist_H)
	{
		ray->rx = play->dvx;
		ray->ry = play->dvy;
		play->dist_final = play->dist_V;
//printf(CYAN"ra = %f"RESET"\n", ray->ra);
		if (ray->ra >= M_PI_2 && ray->ra <= (3 * M_PI_2))
			ray->ray_color = BLUE_PIXEL;
		else if (ray->ra < M_PI_2 || ray->ra >= (3 * M_PI_2))
			ray->ray_color = YELLOW_PIXEL;
	}
	else if (play->dist_H < play->dist_V)
	{
		ray->rx = play->dhx;
		ray->ry = play->dhy;
		play->dist_final = play->dist_H;
		if (ray->ra >= 0 && ray->ra < M_PI)
			ray->ray_color = RED_PIXEL;
		if (ray->ra >= M_PI && ray->ra < 2 * M_PI)
			ray->ray_color = GREEN_PIXEL;
	}
}

float	calcul_dist(float px, float py, float rx, float ry)
{
	return (sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py)));
}

void	define_dist(t_play *play, t_rays *ray, t_map *map, int hv)
{
	while (play->dof < play->end_dof)
	{
printf(GREEN"play->dof = %d | rx = %f | ry = %f"RESET"\n", play->dof, ray->rx, ray->ry);
		ray->mx = (int)(ray->rx) >> 6;
		ray->my = (int)(ray->ry) >> 6;
		ray->mp = ray->my * map->mapX + ray->mx;
//printf(RED"mp = %d | my = %d | mx = %d"RESET"\n", ray->mp, ray->my, ray->mx);
		if (ray->mp > 0 && ray->mp < map->mapS && mapext[ray->mp] == 1) // ray hit wall !
		{
			if (hv == 0)
			{
				play->dhx = ray->rx;
				play->dhy = ray->ry;
		//		if (play->dist_H != 100000)
				play->dist_H = calcul_dist(play->px, play->py, play->dhx, play->dhy);				
			}
			else
			{
				play->dvx = ray->rx;
				play->dvy = ray->ry;
		//		if (play->dist_V != 100000)
				play->dist_V = calcul_dist(play->px, play->py, play->dvx, play->dvy);
			}
// printf(GREEN"rx = %f | ry = %f | distH = %f"RESET"\n", ray->rx, ray->ry, play->dist_H);
//printf(RED"mp = %d | ry = %f | my = %d | rx = %f | mx = %d"RESET"\n", ray->mp, ray->ry, ray->my, ray->rx, ray->mx);
			play->dof = play->end_dof;
		}
		else // make ray go to next wall !
		{
// printf(CYAN"ra = %f | rx = %f | mx = %d | ry = %f | my = %d | ray->mp = [%d]"RESET"\n", ray->ra, ray->rx, ray->mx, ray->ry, ray->my, ray->mp);
			ray->rx += ray->xo;
			ray->ry += ray->yo;
			play->dof += 1;
		}
	}
}

void	check_horizontal(t_data *data, float lim1, float lim2, float tan)
{
	if (data->play.ray.ra == lim1 || data->play.ray.ra == lim2) //-- player is looking left or right
	{
printf(YELLOW"ra = [%f] | player is looking right !"RESET"\n", data->play.ray.ra);
		data->play.ray.ry = data->play.py;
		data->play.ray.rx = data->play.px;
		data->play.dof = data->play.end_dof;
	}
	if (data->play.ray.ra < lim2) //-- player is looking up 
	{
printf(RED"ra = [%f] | player is looking up !"RESET"\n", data->play.ray.ra);
		data->play.ray.ry = (((int)(data->play.py) >> data->map.aire_shift) << data->map.aire_shift) - 0.0001;
		data->play.ray.rx = (data->play.py - data->play.ray.ry) * tan + data->play.px;
		data->play.ray.yo = -data->map.cube_aire;
		data->play.ray.xo = -data->play.ray.yo * tan;
	}
	if (data->play.ray.ra > lim2) //-- player is looking down
	{
printf(GREEN"ra = [%f] | player is looking down!"RESET"\n", data->play.ray.ra);
		data->play.ray.ry = (((int)(data->play.py) >> data->map.aire_shift) << data->map.aire_shift) + data->map.cube_aire;
		data->play.ray.rx = (data->play.py - data->play.ray.ry) * tan + data->play.px;
		data->play.ray.yo = data->map.cube_aire;
		data->play.ray.xo = -data->play.ray.yo * tan;
printf(GREEN"look down : ray->rx = %f | ray->ry = %f"RESET"\n", data->play.ray.rx, data->play.ray.ry);
	}
}

void	check_vertical(t_data *data, float lim1, float lim2, float tan)
{
	if (data->play.ray.ra == lim1 || data->play.ray.ra == lim2) //-- player is looking up or down
	{
//printf(ORANGE"ra = [%f] | player is looking up or down !"RESET"\n", ray->ra);
		data->play.ray.ry = data->play.py;
		data->play.ray.rx = data->play.px;
		data->play.dof = data->play.end_dof;
	}
	if (data->play.ray.ra < lim1 || data->play.ray.ra > lim2) //-- player is looking right
	{
//printf(PURPLE"ra = [%f] | player is looking right !"RESET"\n", ray->ra);
		data->play.ray.rx = (((int)(data->play.px) >> data->map.aire_shift) << data->map.aire_shift) - 0.0001;
		data->play.ray.ry = (data->play.px - data->play.ray.rx) * tan + data->play.py;
		data->play.ray.xo = -data->map.cube_aire;
		data->play.ray.yo = -data->play.ray.xo * tan;
// printf(YELLOW"look right : ray->rx = %f | ray->ry = %f"RESET"\n", ray->rx, ray->ry);
	}
	if (data->play.ray.ra > lim1 && data->play.ray.ra < lim2) //-- player is looking left
	{
//printf(CYAN"look left : ray->rx = %f | play->px = %d | ray->ry = %f | play->py = %d"RESET"\n", ray->rx, play->px, ray->ry, play->py);
		data->play.ray.rx = (((int)(data->play.px) >> data->map.aire_shift) << data->map.aire_shift) + data->map.cube_aire;
		data->play.ray.ry = (data->play.px - data->play.ray.rx) * tan + data->play.py;
		data->play.ray.xo = data->map.cube_aire;
		data->play.ray.yo = -data->play.ray.xo * tan;
// printf(BLUE"look left : ray->rx = %f | play->px = %d | ray->ry = %f | play->py = %d"RESET"\n", ray->rx, play->px, ray->ry, play->py);
	}
}

void	init_rays(t_play *play, t_rays *ray)
{
//	play->pa = play->pa + M_PI;
	ray->ra = play->pa + M_PI - (M_PI / 180 * 30);
	if (ray->ra < 0)
		ray->ra += 2 * M_PI;
	if (ray->ra > 2 * M_PI)
		ray->ra -= 2 * M_PI;
	play->dist_H = 1000000;
	play->dhx = play->px;
	play->dhy = play->py;
	play->dist_V = 1000000;
	play->dvx = play->px;
	play->dvy = play->py;
}

void	draw_rays(t_play *play, t_map *map, t_rays *ray, t_data *data) //ig *img)
{
	int		r;
	float	a_tan;
	float	n_tan;

	init_rays(play, ray);
//printf(GREEN"//-------------------------------------------------------------------------------//"RESET"\n");
//printf(BLUE"ray->ra = %f | play->px = %d | play->py = %d"RESET"\n", ray->ra, play->px, play->py);
	r = 0;
	while (r < 1500) // Taille de la fenetre finale
	{
//--- Check horizontal lines --- video 9'18 -------------------------------------------------------------------------------//
		play->dof = 0;
		a_tan = -1 / tan(ray->ra);
		check_horizontal(data, 0, M_PI, a_tan);
		define_dist(play, ray, map, 0);
//		draw_points(data, play, map, PINK_PIXEL);
//--- Check vertical lines --- video 10'25 -------------------------------------------------------------------------------//
		play->dof = 0;
		n_tan = -tan(ray->ra);
		check_vertical(data, M_PI_2, 3 * M_PI_2, n_tan);
		define_dist(play, ray, map, 1);
//		draw_points(data, play, map, BLACK_PIXEL);
// printf(YELLOW"difference V-H = %f | distV = %f | distH = %f | ra = %f"RESET"\n", play->dist_V - play->dist_H, play->dist_V, play->dist_H, ray->ra);
		define_dist_final(play, ray);
//		draw_ray_0(&data->minimap, play, ray->ra + M_PI, play->dist_H, PINK_PIXEL);
//--- Dessinons les rayons ------------------------------------------------------------------------------------------------//
		draw_points(data, play, map, ray->ray_color);
//printf(YELLOW"difference V-H = %f | distV = %f | distH = %f | ra = %f"RESET"\n", play->dist_V - play->dist_H, play->dist_V, play->dist_H, ray->ra *180 / M_PI);
		draw_3d(play, map, &data->rendu, r);
		ray->ra += ((M_PI / 180.0) * ((60 / 1500.0))); // remettre 60 au lieu de 2
		if (ray->ra < 0)
			ray->ra += 2 * M_PI;
		if (ray->ra > 2 * M_PI)
			ray->ra -= 2 * M_PI;
//printf(ORANGE"//--------------------------------------------------//"RESET"\n");
		r++;
	}
}

// void	draw_rays(t_play *play, t_map *map, t_rays *ray, t_data *data) //ig *img)
// {
// 	int		r;
// 	float	a_tan;
// 	float	n_tan;

// 	init_rays(play, ray);
// printf(GREEN"//-------------------------------------------------------------------------------//"RESET"\n");
// printf(BLUE"ray->ra = %f | play->px = %d | play->py = %d"RESET"\n", ray->ra, play->px, play->py);
// 	r = 0;
// 	while (r < 1500) // Taille de la fenetre finale
// 	{
// /*--- Check horizontal lines --- video 9'18 -----------------------------------------------------------------------------------*/
// 		play->dof = 0;
// 		a_tan = -1 / tan(ray->ra);
// 		if (ray->ra == 0.000000 || ray->ra == M_PI) //-- player is looking left or right
// 		{
// //printf(YELLOW"ra = [%f] | player is looking right !"RESET"\n", ray->ra);
// 			ray->ry = play->py;
// 			ray->rx = play->px;
// 			play->dof = 8;
// 		}
// 		if (ray->ra < M_PI) //-- player is looking up 
// 		{
// //printf(RED"ra = [%f] | player is looking up !"RESET"\n", ray->ra);
// //			if (((((int)(play->py) >> 6) << 6) - 0.0001) < map->len_mapYS && ((((int)(play->py) >> 6) << 6) - 0.0001) > 0)
// 				ray->ry = (((int)(play->py) >> 6) << 6) - 0.0001;
// //			if (((play->py - ray->ry) * a_tan + play->px) < map->len_mapXS && ((play->py - ray->ry) * a_tan + play->px) > 0)
// 				ray->rx = (play->py - ray->ry) * a_tan + play->px;
// 			ray->yo = -64;
// 			ray->xo = -ray->yo * a_tan;
// //printf(RED"look up : ray->rx = %f | ray->ry = %f"RESET"\n", ray->rx, ray->ry);
// 		}
// 		if (ray->ra > M_PI) //-- player is looking down
// 		{
// //printf(GREEN"ra = [%f] | player is looking down!"RESET"\n", ray->ra);
// //			if (((((int)(play->py) >> 6) << 6) + 64) < map->len_mapYS && ((((int)(play->py) >> 6) << 6) + 64) > 0)
// 				ray->ry = (((int)(play->py) >> 6) << 6) + 64;
// 			// else
// 			// 	ray->ry = (((int)(play->py) >> 6) << 6);
// //			if (((play->py - ray->ry) * a_tan + play->px) < map->len_mapXS && ((play->py - ray->ry) * a_tan + play->px) > 0)
// 				ray->rx = (play->py - ray->ry) * a_tan + play->px;
// 			// if (ray->ry > map->len_mapYS || ray->ry < 0 || ray->rx > map->len_mapXS || ray->rx < 0)
// 			// 	continue;
// //printf(GREEN"ry = %f"RESET"\n", ray->ry);
// 			ray->yo = 64;
// 			ray->xo = -ray->yo * a_tan;
// // printf(GREEN"look down : ray->rx = %f | ray->ry = %f"RESET"\n", ray->rx, ray->ry);
// 		}
// 		// if (ray->ry > map->len_mapYS || ray->ry < 0 || ray->rx > map->len_mapXS || ray->rx < 0)
// 		// 	continue;
// 		while (play->dof < 8)
// 		{
// // printf(GREEN"play->dof = %d | rx = %f | ry = %f"RESET"\n", play->dof, ray->rx, ray->ry);
// //			if (ray->rx > 0)
// //			{
// 			// if (ray->rx > map->len_mapXS)
// 			// {
// 			// 	ray->rx = map->len_mapXS;
// 			// 	play->dist_H = 100000;
// 			// 	play->dof = 8;
// 			// }
// 			// if (ray->rx < 0)
// 			// {
// 			// 	ray->rx = 0;
// 			// 	play->dist_H = 100000;
// 			// 	play->dof = 8;
// 			// }				
// 			ray->mx = (int)(ray->rx) >> 6;
// //			}
// //			if (ray->ry > 0)
// //			{
// // 			if (ray->ry > map->len_mapYS)
// // 			{
// // 				ray->ry = map->len_mapYS;
// // 				play->dist_H = 100000;
// // 				play->dof = 8;				
// // 			}
// // 			if (ray->ry < 0)
// // 			{
// // 				ray->ry = 0;
// // 				play->dist_H = 100000;
// // 				play->dof = 8;
// // 			}
// // printf(CYAN"ry = %f"RESET"\n", ray->ry);
// 			ray->my = (int)(ray->ry) >> 6;
// //			}
// 			ray->mp = ray->my * map->mapX + ray->mx;
// //printf(RED"mp = %d | my = %d | mapX = %d | mx = %d"RESET"\n", ray->mp, ray->my, map->mapX, ray->mx);
// 			if (ray->mp > 0 && ray->mp < map->mapS && mapext[ray->mp] == 1) // ray hit wall !
// 			{
// 				play->dhx = ray->rx;
// 				play->dhy = ray->ry;
// 				if (play->dist_H != 100000)
// 					play->dist_H = calcul_dist(play->px, play->py, play->dhx, play->dhy);
// // printf(GREEN"rx = %f | ry = %f | distH = %f"RESET"\n", ray->rx, ray->ry, play->dist_H);
// //printf(RED"mp = %d | ry = %f | my = %d | rx = %f | mx = %d"RESET"\n", ray->mp, ray->ry, ray->my, ray->rx, ray->mx);
// 				play->dof = 8;
// 			}
// 			else // make ray go to next wall !
// 			{
// // printf(CYAN"ra = %f | rx = %f | mx = %d | ry = %f | my = %d | ray->mp = [%d]"RESET"\n", ray->ra, ray->rx, ray->mx, ray->ry, ray->my, ray->mp);
// 			//	if (((ray->rx + ray->xo) < map->len_mapXS && (ray->rx + ray->xo) > 0))
// 					ray->rx += ray->xo;
// 				//else
// 				//	play->dof = 8;
// 			//	if ((ray->ry + ray->yo) < map->len_mapYS && (ray->ry + ray->yo) > 0)
// 					ray->ry += ray->yo;
// 				//else
// 				//	play->dof = 8;
// 				play->dof += 1;
// 			}
// 		}
// //		draw_points(data, play, map, PINK_PIXEL);
// /* --- Check vertical lines --- video 10'25 ------------------------------------------------------------------------------------------------------*/
// 		play->dof = 0;
// 		n_tan = -tan(ray->ra);
// 		if (ray->ra == M_PI_2 || ray->ra == 3 * M_PI_2) //-- player is looking up or down
// 		{
// //printf(ORANGE"ra = [%f] | player is looking up or down !"RESET"\n", ray->ra);
// 			ray->ry = play->py;
// 			ray->rx = play->px;
// 			play->dof = 8;
// 		}
// 		else if (ray->ra < (M_PI_2) || ray->ra > (3 * M_PI_2)) //-- player is looking right
// 		{
// //printf(PURPLE"ra = [%f] | player is looking right !"RESET"\n", ray->ra);
// 		//	if (((((int)(play->px) >> 6) << 6) - 0.0001) < map->len_mapXS && ((((int)(play->px) >> 6) << 6) - 0.0001) > 0)
// 				ray->rx = (((int)(play->px) >> 6) << 6) - 0.0001;
// 		//	if (((play->px - ray->rx) * n_tan + play->py) < map->len_mapYS && ((play->px - ray->rx) * n_tan + play->py) > 0)
// 				ray->ry = (play->px - ray->rx) * n_tan + play->py;
// 			ray->xo = -64;
// 			ray->yo = -ray->xo * n_tan;
// // printf(YELLOW"look right : ray->rx = %f | ray->ry = %f"RESET"\n", ray->rx, ray->ry);
// 		}
// 		else if (ray->ra > (M_PI_2) && ray->ra < (2 * M_PI / 3)) //-- player is looking left
// 		{
// //printf(CYAN"look left : ray->rx = %f | play->px = %d | ray->ry = %f | play->py = %d"RESET"\n", ray->rx, play->px, ray->ry, play->py);
// 		//	if (((((int)(play->px) >> 6) << 6) + 64) < map->len_mapYS && ((((int)(play->px) >> 6) << 6) + 64) > 0)
// 				ray->rx = (((int)(play->px) >> 6) << 6) + 64;
// 		//	if (((play->px - ray->rx) * n_tan + play->py) < map->len_mapXS && ((play->px - ray->rx) * n_tan + play->py) > 0)
// 				ray->ry = (play->px - ray->rx) * n_tan + play->py;
// 			ray->xo = 64;
// 			ray->yo = -ray->xo * n_tan;
// // printf(BLUE"look left : ray->rx = %f | play->px = %d | ray->ry = %f | play->py = %d"RESET"\n", ray->rx, play->px, ray->ry, play->py);
// 		}
// 		while (play->dof < 8)
// 		{
// // printf(PURPLE"play->dof = %d | rx = %f | ry = %f"RESET"\n", play->dof, ray->rx, ray->ry);
// 			// if (ray->rx > 0)
// 			// 	if (ray->rx < map->len_mapXS)
// 					ray->mx = (int)(ray->rx) >> 6;
// 			// if (ray->ry > 0)
// 			// 	if (ray->ry < map->len_mapYS)
// 					ray->my = (int)(ray->ry) >> 6;
// 			ray->mp = ray->my * map->mapX + ray->mx;
// 			if (ray->mp > 0 && ray->mp < map->mapS && mapext[ray->mp] == 1) // ray hit wall !
// 			{
// 				play->dvx = ray->rx;
// 				play->dvy = ray->ry;
// 				play->dist_V = calcul_dist(play->px, play->py, play->dvx, play->dvy);
// // printf(PURPLE"rx = %f | ry = %f | distV = %f"RESET"\n", ray->rx, ray->ry, play->dist_V);
// 				play->dof = 8;
// 			}
// 			else // make ray go to next wall !
// 			{
// // printf(BLUE"ra = %f | rx = %f | mx = %d | ry = %f | my = %d | ray->mp = [%d]"RESET"\n", ray->ra, ray->rx, ray->mx, ray->ry, ray->my, ray->mp);
// 			//	if (ray->rx < map->len_mapXS && (ray->rx + ray->xo) < map->len_mapXS && (ray->rx + ray->xo) > 0)
// 					ray->rx += ray->xo;
// 			//	if (ray->ry < map->len_mapYS && (ray->ry + ray->yo) < map->len_mapYS && (ray->ry + ray->yo) > 0)
// 					ray->ry += ray->yo;
// 				play->dof += 1;
// 			}
// 		}
// 	//	draw_points(data, play, map, BLACK_PIXEL);
// // printf(YELLOW"difference V-H = %f | distV = %f | distH = %f | ra = %f"RESET"\n", play->dist_V - play->dist_H, play->dist_V, play->dist_H, ray->ra);
// 		define_dist_final(play, ray);
// 		// if (play->dist_V < play->dist_H)
// 		// {
// 		// 	ray->rx = play->dvx;
// 		// 	ray->ry = play->dvy;
// 		// 	play->dist_final = play->dist_V;
// 		// 	if (ray->ra <= M_PI_2 || ray->ra > 2 * M_PI / 3)
// 		// 		ray->ray_color = BLUE_PIXEL;
// 		// 	if (ray->ra > M_PI_2 && ray->ra <= 2 * M_PI / 3)
// 		// 		ray->ray_color = YELLOW_PIXEL;
// 		// }
// 		// else if (play->dist_H < play->dist_V)
// 		// {
// 		// 	ray->rx = play->dhx;
// 		// 	ray->ry = play->dhy;
// 		// 	play->dist_final = play->dist_H;
// 		// 	if (ray->ra >= 0 && ray->ra < M_PI)
// 		// 		ray->ray_color = RED_PIXEL;
// 		// 	if (ray->ra >= M_PI && ray->ra < 2 * M_PI)
// 		// 		ray->ray_color = GREEN_PIXEL;
// 		// }
// //		draw_ray_0(&data->minimap, play, ray->ra + M_PI, play->dist_H, PINK_PIXEL);

// 	//---dessinons les rayons ---//
// 		// int i, j;
// 		// i = play->ray.ry; // On affiche le point de contact du rayon avec les murs
// 		// while (i < play->ray.ry + 3 && i < map->len_mapYS)
// 		// {
// 		// 	j = play->ray.rx;
// 		// 	while (j < play->ray.rx + 3 && j < map->len_mapXS)
// 		// 		my_pixel_put(&data->minimap, j++, i, ray->ray_color);
// 		// 	++i;
// 		// }
// 		draw_points(data, play, map, ray->ray_color);
// //printf(YELLOW"difference V-H = %f | distV = %f | distH = %f | ra = %f"RESET"\n", play->dist_V - play->dist_H, play->dist_V, play->dist_H, ray->ra *180 / M_PI);
// 		draw_3d(play, map, &data->rendu, r);
// 		ray->ra += ((M_PI / 180.0) * ((60 / 1500.0))); // remettre 60 au lieu de 2
// 		if (ray->ra < 0)
// 			ray->ra += 2 * M_PI;
// 		if (ray->ra > 2 * M_PI)
// 			ray->ra -= 2 * M_PI;
// //printf(ORANGE"//--------------------------------------------------//"RESET"\n");
// 		r++;
// 	}
// }

int	render_player(t_ig *img, t_play play)
{
	int	i;
	int	j;

	i = play.py - play.height; // On affiche le player
	while (i < play.py + play.height)
	{
		j = play.px - play.width;
		while (j < play.px + play.width)
			my_pixel_put(img, j++, i, play.color);
		++i;
	}
//printf(RED"pa = %f"RESET"\n", play.pa);
	i = play.py + play.pdy * 5; // On affiche la direction dans laquelle le player regarde ! ATTENTION PB !
	while (i < play.py + play.pdy * 5 + play.height)
	{
		j = play.px + play.pdx * 5;
		while (j < play.px + play.pdx * 5 + play.width)
			my_pixel_put(img, j++, i, GREEN_PIXEL);
		++i;
	}
	return (0);
}

int	fill_cube(t_ig *img, t_map *map, int x, int y, int color)
{
	int	begin_x;
	int	begin_y;
	int	i;
	int	j;

	begin_x = x * map->cube_aire;
	begin_y = y * map->cube_aire;
	j = begin_y;
	while (j < begin_y + map->cube_aire)
	{
		i = begin_x;
		while (i < begin_x + map->cube_aire)
		{
			if (i == begin_x + map->cube_aire - 1 || j == begin_y + map->cube_aire - 1)
				my_pixel_put(img, i, j, BLACK_PIXEL);
			else
				my_pixel_put(img, i, j, color);
			i++;
		}
		j++;
	}
	return (0);
}

int	render_map(t_ig *img, t_map map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map.mapY)
	{
		x = 0;
		while (x < map.mapX)
		{
			if (mapext[y * map.mapX + x] == 1)
				fill_cube(img, &map, x, y, WHITE_PIXEL);
			else
				fill_cube(img, &map, x, y, GRAY_PIXEL);
			x++;
		}
		y++;
	}
	return (0);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_map(&data->minimap, data->map);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->minimap.mlx_img, 0, 0);
	render_background(&data->rendu, data->rendu.ceil_color, data->rendu.floor_color);
	render_player(&data->minimap, data->play);
	//draw_ray_0(&data->minimap, &data->play, data->play.pa, 64, );
	draw_rays(&data->play, &data->map, &data->play.ray, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rendu.mlx_img, data->map.len_mapXS + 15, 0);
	return (0);
}

int	next_pos_is_wall(t_data *data, int sens)
{
	int	index;
	int	next_x;
	int	next_y;

	if (sens == 1)
	{
		next_x = (data->play.px + data->play.pdx) / data->map.cube_aire;
		next_y = (data->play.py + data->play.pdy) / data->map.cube_aire;
	}
	else
	{
		next_x = (data->play.px - data->play.pdx) / data->map.cube_aire;
		next_y = (data->play.py - data->play.pdy) / data->map.cube_aire;
	}
	index = next_y * data->map.mapX + next_x;
printf(YELLOW"index = %d || mapext[index] = %d"RESET"\n", index, mapext[index]);
	if (mapext[index] == 1)
		return (1);
	else
		return (0);
}

void	turn_right(t_data *data)
{
printf("right\n");
	data->play.pa += 0.1;
	if (data->play.pa > 2 * M_PI)
		data->play.pa -= 2 * M_PI;
	data->play.pdx = cos(data->play.pa) * 5;
	data->play.pdy = sin(data->play.pa) * 5;
}

void	turn_left(t_data *data)
{
printf("left\n");
	data->play.pa -= 0.1;
	if (data->play.pa < 0)
		data->play.pa += 2 * M_PI;
	data->play.pdx = cos(data->play.pa) * 5;
	data->play.pdy = sin(data->play.pa) * 5;
}

void	move_right(t_data *data)
{
printf("D\n");
	data->play.px += data->play.pdy;
	data->play.py -= data->play.pdx;
}

void	move_left(t_data *data)
{
printf("A\n");
	data->play.px -= data->play.pdy;
	data->play.py += data->play.pdx;
}

void	move_forward(t_data *data)
{
printf("W\n");
	data->play.px += data->play.pdx;
	data->play.py += data->play.pdy;
}

void	move_backward(t_data *data)
{
printf("S\n");
	data->play.px -= data->play.pdx;
	data->play.py -= data->play.pdy;
}

int	ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

int	deal_key(int key, t_data *data)
{
	if ((key == 115 || key == 65364) && !next_pos_is_wall(data, 1)) // touche S
		move_backward(data);
	if ((key == 119 || key == 65362) && !next_pos_is_wall(data, 0)) // touche W
		move_forward(data);
	if (key == 97 && !next_pos_is_wall(data, 1))
		move_left(data);
	if (key == 100 && !next_pos_is_wall(data, 0))
		move_right(data);
	if (key == 65361)
		turn_left(data);
	if (key == 65363)
		turn_right(data);
	if (key == 65307)
		ft_close(data);
	return (0);
}

void	init_data(t_data *data)
{
	data->rendu.ceil_color = 0xFFFF;
	data->rendu.floor_color = 0xFF7F50;
	data->play.px = 40;
	data->play.py = 40;
	data->play.width = 3; /* A retirer plus tard */
	data->play.height = 3; /* A retirer plus tard */
	data->play.color = 0x00FF0000;
	data->play.pa = 0;//M_PI_2 + M_PI;
	data->play.pdx = sin(data->play.pa);//cos(data->play.pa);/* * 5; */
	data->play.pdy = cos(data->play.pa);//sin(data->play.pa);/* * 5; */
	data->play.dist_H = 1000000;
	data->play.dist_V = 1000000;
	data->map.mapX = 20;
	data->map.mapY = 8;
	if (data->map.mapX > data->map.mapY)
		data->play.end_dof = data->map.mapX;
	else
		data->play.end_dof = data->map.mapY;
	data->map.cube_aire = 32;
	data->map.aire_shift = data->map.cube_aire / 10;
printf(GREEN"aire_shift = %d"RESET"\n", data->map.aire_shift);
	data->map.mapS = 160;
	data->map.len_mapXS = data->map.mapX * data->map.cube_aire;
	data->map.len_mapYS = data->map.mapY * data->map.cube_aire;
}

int	main(void)
{
	t_data	data;

	init_data(&data);
/*//	data.map.map = mapext;
	// data.map.map =
	// {
	// 1,1,1,1,1,1,1,1,
	// 1,0,1,0,0,0,0,1,
	// 1,0,1,0,0,0,0,1,
	// 1,0,1,0,0,0,0,1,
	// 1,0,0,0,0,0,0,1,
	// 1,0,0,0,0,1,0,1,
	// 1,0,0,0,0,0,0,1,
	// 1,1,1,1,1,1,1,1,
	// };*/
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "Cub3D_test");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (1);
	}
	data.minimap.mlx_img = mlx_new_image(data.mlx_ptr, data.map.len_mapXS, data.map.len_mapYS);
	data.minimap.addr = mlx_get_data_addr(data.minimap.mlx_img, &data.minimap.bpp, &data.minimap.line_len, &data.minimap.endian);
	data.rendu.mlx_img = mlx_new_image(data.mlx_ptr, 1500, 900); // A MODIFIER
	data.rendu.addr = mlx_get_data_addr(data.rendu.mlx_img, &data.rendu.bpp, &data.rendu.line_len, &data.rendu.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
/*	mlx_mouse_hook(data.win_ptr, deal_mouse, &data); // si un jour on veut utiliser la souris */
/* ATTENTION : différence entre mlx_key_hook et mlx_hook ! mlx_key_hook : la fct ne s'active que
lorsque le bouton est relaché ! mlx_hook : la fct s'active lorsque le bouton est pressé !!!*/
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &deal_key, &data); // for quitting via escape keyboard key 
	mlx_hook(data.win_ptr, 17, 1L << 17, ft_close, &data); // for quitting via mouse on window cross
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.minimap.mlx_img);
	mlx_destroy_image(data.mlx_ptr, data.rendu.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}

/* video 11'35 tracer le plus petit des rayons (hit Vertical ou hit Horizontal) */
/* https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx */
