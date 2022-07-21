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

void	my_pixel_put(t_img *img, int x, int y, int color)
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

void	render_background(t_img *img, int c, int f)
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

void	draw_3d(t_play *play, t_map *map, t_img *img, int r)
{
	int		i;
	int		j;
	float	line_origin;
	float	fish_eye;
	float	line_h;

	fish_eye = play->pa - play->ray.ra;
	if (fish_eye < 0)
		fish_eye += 2 * M_PI;
	if (fish_eye > 2 * M_PI)
		fish_eye -= 2 * M_PI;
	play->dist_final = play->dist_final * cos(fish_eye);
	line_h = map->mapS * W_HEIGHT / play->dist_final;
	if (line_h > W_HEIGHT)
		line_h = W_HEIGHT;
	line_origin = (W_HEIGHT / 2) - line_h / 2;
	i = line_origin;
	while (i < line_h + line_origin)
	{
		j = r * 25 + 530;
		while (j < (r * 25 + 530) + 25)//(j < (r * 8 + 530) + 8)
			my_pixel_put(img, j++, i, play->ray.ray_color);
		++i;
	}
}

float	calcul_dist(float px, float py, float rx, float ry)
{
	return (sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py)));
}

void	draw_rays(t_play *play, t_map *map, t_rays *ray, t_img *img)
{
	int		r;
//	int		dof;
	float	a_tan;
	float	n_tan;

	ray->ra = play->pa - (M_PI / 180 * 30);
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
printf(ORANGE"//--------------------------------------------------//"RESET"\n");
printf(BLUE"play->pa = %f | ray->ra = %f | play->px = %d | play->py = %d"RESET"\n", play->pa, ray->ra, play->px, play->py);
	r = 0;
	while (r < 60)
	{
/*--- Check horizontal lines --- video 9'18 ---*/
		play->dof = 0;
		a_tan = -1 / tan(ray->ra);
		if (ray->ra == 0 || ray->ra == M_PI || ray->ra == 2 * M_PI) //-- player is looking left or right
		{
//printf(YELLOW"ra = [%f] | player is looking left or right !"RESET"\n", ray->ra);
			ray->ry = play->py;
			ray->rx = play->px;
			play->dof = 8;
		}
		else if (ray->ra < M_PI) //-- player is looking up 
		{
//printf(RED"ra = [%f] | player is looking up !"RESET"\n", ray->ra);
			if (((((int)(play->py) >> 6) << 6) - 0.0001) < map->len_mapYS && ((((int)(play->py) >> 6) << 6) - 0.0001) > 0)
				ray->ry = (((int)(play->py) >> 6) << 6) - 0.0001;
			if (((play->py - ray->ry) * a_tan + play->px) < map->len_mapXS && ((play->py - ray->ry) * a_tan + play->px) > 0)
				ray->rx = (play->py - ray->ry) * a_tan + play->px;
			ray->yo = -64;
			ray->xo = -ray->yo * a_tan;
printf(RED"look up : ray->rx = %f | ray->ry = %f"RESET"\n", ray->rx, ray->ry);
		}
		else if (ray->ra > M_PI) //-- player is looking down
		{
//printf(GREEN"ra = [%f] | player is looking down!"RESET"\n", ray->ra);
			if (((((int)(play->py) >> 6) << 6) + 64) < map->len_mapYS && ((((int)(play->py) >> 6) << 6) + 64) > 0)
				ray->ry = (((int)(play->py) >> 6) << 6) + 64;
			if (((play->py - ray->ry) * a_tan + play->px) < map->len_mapXS && ((play->py - ray->ry) * a_tan + play->px) > 0)
				ray->rx = (play->py - ray->ry) * a_tan + play->px;
			ray->yo = 64;
			ray->xo = -ray->yo * a_tan;
printf(GREEN"look down : ray->rx = %f | ray->ry = %f"RESET"\n", ray->rx, ray->ry);
		}
		while (play->dof < 8)
		{
printf(GREEN"play->dof = %d | rx = %f | ry = %f"RESET"\n", play->dof, ray->rx, ray->ry);
			if (ray->rx > 0)
			{
				if (ray->rx > map->len_mapXS)
					ray->rx = map->len_mapXS;
				ray->mx = (int)(ray->rx) >> 6;
			}
			if (ray->ry > 0)
			{
				if (ray->ry > map->len_mapYS)
					ray->ry = map->len_mapYS;
				ray->my = (int)(ray->ry) >> 6;
			}
			ray->mp = ray->my * map->mapX + ray->mx;
printf(RED"mp = %d | my = %d | mapX = %d | mx = %d"RESET"\n", ray->mp, ray->my, map->mapX, ray->mx);
			if (ray->mp > 0 && ray->mp < map->mapS && mapext[ray->mp] == 1) // ray hit wall !
			{
				play->dhx = ray->rx;
				play->dhy = ray->ry;
				play->dist_H = calcul_dist(play->px, play->py, play->dhx, play->dhy);
printf(GREEN"rx = %f | ry = %f | distH = %f"RESET"\n", ray->rx, ray->ry, play->dist_H);
				play->dof = 8;
			}
			else // make ray go to next wall !
			{
printf(CYAN"ra = %f | rx = %f | mx = %d | ry = %f | my = %d | ray->mp = [%d]"RESET"\n", ray->ra, ray->rx, ray->mx, ray->ry, ray->my, ray->mp);
				if (ray->rx < map->len_mapXS && (ray->rx + ray->xo) < map->len_mapXS && (ray->rx + ray->xo) > 0)
					ray->rx += ray->xo;
				if (ray->ry < map->len_mapYS && (ray->ry + ray->yo) < map->len_mapYS && (ray->ry + ray->yo) > 0)
					ray->ry += ray->yo;
				play->dof += 1;
			}
		}
// // //---dessinons les rayons horizontaux ! ---//
// 		int a, b;
// 		a = play->ray.ry + play->height;//play.ray.ry; // On affiche le point de contact du rayon avec l'horizontale
// //	printf(YELLOW"a = %d"RESET"\n", a);
// 		while (a > play->ray.ry && a < map->len_mapYS)// < play.ray.ry + play.height)
// 		{
// 			b = play->ray.rx;
// //	printf(ORANGE"b = %d"RESET"\n", b);
// 			while (b < play->ray.rx + play->width && b < map->len_mapXS)
// 			{
// //	printf(BLUE"a = %d | b = %d"RESET"\n", a, b);
// 				my_pixel_put(img, b++, a, BLACK_PIXEL);
// 			}
// 			--a;
// 		}
// 		r++;
/* --- Check vertical lines --- video 10'25 --*/
		play->dof = 0;
		n_tan = -tan(ray->ra);
		if (ray->ra == 0 || ray->ra == M_PI || ray->ra == 2 * M_PI) //-- player is looking up or down
		{
//printf(ORANGE"ra = [%f] | player is looking up or down !"RESET"\n", ray->ra);
			ray->ry = play->py;
			ray->rx = play->px;
			play->dof = 8;
		}
		else if (ray->ra < (M_PI / 2) || ray->ra > (3 * M_PI / 2)) //-- player is looking right
		{
//printf(PURPLE"ra = [%f] | player is looking left !"RESET"\n", ray->ra);
			if (((((int)(play->px) >> 6) << 6) - 0.0001) < map->len_mapXS && ((((int)(play->px) >> 6) << 6) - 0.0001) > 0)
				ray->rx = (((int)(play->px) >> 6) << 6) - 0.0001;
			if (((play->px - ray->rx) * n_tan + play->py) < map->len_mapYS && ((play->px - ray->rx) * n_tan + play->py) > 0)
				ray->ry = (play->px - ray->rx) * n_tan + play->py;
			ray->xo = -64;
			ray->yo = -ray->xo * n_tan;
printf(YELLOW"look right : ray->rx = %f | ray->ry = %f"RESET"\n", ray->rx, ray->ry);
		}
		else if (ray->ra > (M_PI / 2) && ray->ra < (3 * M_PI / 2)) //-- player is looking left
		{
//printf(CYAN"look left : ray->rx = %f | play->px = %d | ray->ry = %f | play->py = %d"RESET"\n", ray->rx, play->px, ray->ry, play->py);
			if (((((int)(play->px) >> 6) << 6) + 64) < map->len_mapYS && ((((int)(play->px) >> 6) << 6) + 64) > 0)
				ray->rx = (((int)(play->px) >> 6) << 6) + 64;
			if (((play->px - ray->rx) * n_tan + play->py) < map->len_mapXS && ((play->px - ray->rx) * n_tan + play->py) > 0)
				ray->ry = (play->px - ray->rx) * n_tan + play->py;
			ray->xo = 64;
			ray->yo = -ray->xo * n_tan;
printf(BLUE"look left : ray->rx = %f | play->px = %d | ray->ry = %f | play->py = %d"RESET"\n", ray->rx, play->px, ray->ry, play->py);
		}
		while (play->dof < 8)
		{
printf(PURPLE"play->dof = %d | rx = %f | ry = %f"RESET"\n", play->dof, ray->rx, ray->ry);
			if (ray->rx > 0)
				if (ray->rx < map->len_mapXS)
					ray->mx = (int)(ray->rx) >> 6;
			if (ray->ry > 0)
				if (ray->ry < map->len_mapYS)
					ray->my = (int)(ray->ry) >> 6;
			ray->mp = ray->my * map->mapX + ray->mx;
			if (ray->mp > 0 && ray->mp < map->mapS && mapext[ray->mp] == 1) // ray hit wall !
			{
				play->dvx = ray->rx;
				play->dvy = ray->ry;
				play->dist_V = calcul_dist(play->px, play->py, play->dvx, play->dvy);
printf(PURPLE"rx = %f | ry = %f | distV = %f"RESET"\n", ray->rx, ray->ry, play->dist_V);
				play->dof = 8;
			}
			else // make ray go to next wall !
			{
printf(BLUE"ra = %f | rx = %f | mx = %d | ry = %f | my = %d | ray->mp = [%d]"RESET"\n", ray->ra, ray->rx, ray->mx, ray->ry, ray->my, ray->mp);
				if (ray->rx < map->len_mapXS && (ray->rx + ray->xo) < map->len_mapXS && (ray->rx + ray->xo) > 0)
					ray->rx += ray->xo;
				if (ray->ry < map->len_mapYS && (ray->ry + ray->yo) < map->len_mapYS && (ray->ry + ray->yo) > 0)
					ray->ry += ray->yo;
				play->dof += 1;
			}
		}
// //---dessinons les rayons verticaux ! ---//
// 		int c, d;
// 		c = play->ray.ry + play->height;//play.ray.ry; // On affiche le point de contact du rayon avec l'horizontale
// //	printf(YELLOW"c = %d"RESET"\n", c);
// 		while (c > play->ray.ry && c < map->len_mapYS)// < play.ray.ry + play.height)
// 		{
// 			d = play->ray.rx;
// //	printf(ORANGE"d = %d"RESET"\n", d);
// 			while (d < play->ray.rx + play->width && d < map->len_mapXS)
// 			{
// //	printf(BLUE"c = %d | d = %d"RESET"\n", c, d);
// 				my_pixel_put(img, d++, c, PINK_PIXEL);
// 			}
// 			--c;
// 		}
printf(YELLOW"difference V-H = %f | distV = %f | distH = %f | ra = %f"RESET"\n", play->dist_V - play->dist_H, play->dist_V, play->dist_H, ray->ra);
		if (play->dist_V < play->dist_H)
		{
			ray->rx = play->dvx;
			ray->ry = play->dvy;
			play->dist_final = play->dist_V;
			if (ray->ra <= M_PI / 2 || ray->ra > 2 * M_PI / 3)
				ray->ray_color = BLUE_PIXEL;
			if (ray->ra > M_PI / 2 && ray->ra <= 2 * M_PI / 3)
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
	//---dessinons les rayons ---//
		int i, j;
		i = play->ray.ry; // On affiche le point de contact du rayon avec les murs
		while (i < play->ray.ry + 3 && i < map->len_mapYS)
		{
			j = play->ray.rx;
			while (j < play->ray.rx + 3 && j < map->len_mapXS)
				my_pixel_put(img, j++, i, ray->ray_color);
			++i;
		}
		draw_3d(play, map, img, r);
		ray->ra += M_PI / 180;
		if (ray->ra < 0)
			ray->ra += 2 * M_PI;
		if (ray->ra > 2 * M_PI)
			ray->ra -= 2 * M_PI;
printf(ORANGE"//--------------------------------------------------//"RESET"\n");
		r++;
	}
}

int	render_player(t_img *img, t_play play)
{
	int	i;
	int	j;

	i = play.py; // On affiche le player
	while (i < play.py + play.height)
	{
		j = play.px;
		while (j < play.px + play.width)
			my_pixel_put(img, j++, i, play.color);
		++i;
	}
	/*// i = play.py + play.pdy * 5; // On affiche sa direction !
	// while (i < play.py + play.pdy * 5 + play.height)
	// {
	// 	j = play.px + play.pdx * 5;
	// 	while (j < play.px + play.pdx * 5 + play.width)
	// 		my_pixel_put(img, j++, i, GREEN_PIXEL);
	// 	++i;
	// }*/
	return (0);
}

int	fill_cube(t_img *img, t_map *map, int x, int y, int color)
{
	int	begin_x;
	int	begin_y;
	int	i;
	int	j;

	begin_x = x * map->mapS;
	begin_y = y * map->mapS;
	j = begin_y;
	while (j < begin_y + map->mapS)
	{
		i = begin_x;
		while (i < begin_x + map->mapS)
		{
			if (i == begin_x + map->mapS - 1 || j == begin_y + map->mapS - 1)
				my_pixel_put(img, i, j, BLACK_PIXEL);
			else
				my_pixel_put(img, i, j, color);
			i++;
		}
		j++;
	}
	return (0);
}

int	render_map(t_img *img, t_map map)
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
	render_map(&data->img, data->map);
	render_background(&data->img, data->img.ceil_color, data->img.floor_color);
	render_player(&data->img, data->play);
	draw_rays(&data->play, &data->map, &data->play.ray, &data->img);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	next_pos_is_wall(t_data *data, int sens)
{
	int	index;
	int	next_x;
	int	next_y;

	if (sens == 1)
	{
		next_x = (data->play.px + data->play.pdx) / data->map.mapS;
		next_y = (data->play.py + data->play.pdy) / data->map.mapS;
	}
	else
	{
		next_x = (data->play.px - data->play.pdx) / data->map.mapS;
		next_y = (data->play.py - data->play.pdy) / data->map.mapS;
	}
	index = next_y * data->map.mapX + next_x;
	if (mapext[index] == 1)
		return (1);
	else
		return (0);
}

int	deal_key(int key, t_data *data)
{
	if (key == 115 && !next_pos_is_wall(data, 1))
	{
printf("S\n");
		data->play.px += data->play.pdx;
		data->play.py += data->play.pdy;
	}
	if (key == 119 && !next_pos_is_wall(data, 0))
	{
printf("W\n");
		data->play.px -= data->play.pdx;
		data->play.py -= data->play.pdy;
	}
	if (key == 97)
	{
printf("A\n");
		data->play.pa -= 0.1;
		if (data->play.pa < 0)
			data->play.pa += 2 * M_PI;
		data->play.pdx = cos(data->play.pa) * 5;
		data->play.pdy = sin(data->play.pa) * 5;
	}
	if (key == 100)
	{
printf("D\n");
		data->play.pa += 0.1;
		if (data->play.pa > 2 * M_PI)
			data->play.pa -= 2 * M_PI;
		data->play.pdx = cos(data->play.pa) * 5;
		data->play.pdy = sin(data->play.pa) * 5;
	}
	if (key == 65307)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	main(void)
{
	t_data	data;

/*---- initialisations de donnees ----*/
	data.img.ceil_color = 0xFFFF;
	data.img.floor_color = 0xFF7F50;
	data.play.px = 300;
	data.play.py = 300;
	data.play.width = 5; /* A retirer plus tard */
	data.play.height = 5; /* A retirer plus tard */
	data.play.color = 0x00FF0000;
	data.play.pa = 0; //M_PI;
	data.play.pdx = cos(data.play.pa);/* * 5; */
	data.play.pdy = sin(data.play.pa);/* * 5; */
	data.play.dist_H = 1000000;
	data.play.dist_V = 1000000;
	data.map.mapX = 8;
	data.map.mapY = 8;
	data.map.mapS = 64;
	data.map.len_mapXS = data.map.mapX * data.map.mapS;
	data.map.len_mapYS = data.map.mapY * data.map.mapS;
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
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
/*	mlx_mouse_hook(data.win_ptr, deal_mouse, &data); // si un jour on veut utiliser la souris */
/* ATTENTION : différence entre mlx_key_hook et mlx_hook ! mlx_key_hook : la fct ne s'active que
lorsque le bouton est relaché ! mlx_hook : la fct s'active lorsque le bouton est pressé !!!*/
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &deal_key, &data); // for escape and quit
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}

/* video 11'35 tracer le plus petit des rayons (hit Vertical ou hit Horizontal) */
/* https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx */
