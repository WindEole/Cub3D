#include "cub3d.h"
#include "X11/X.h"

# define W_WIDTH 600
# define W_HEIGHT 300

# define GREEN_PIXEL 0xFF00
# define RED_PIXEL 0x00FF0000
# define BLUE_PIXEL 0xFF
# define WHITE_PIXEL 0xFFFFFF
# define GRAY_PIXEL 0x808080
# define BLACK_PIXEL 0x000000
# define YELLOW_PIXEL 0xFFFF00

# define PI 3.141593

# define CEILING 0xFFFF
# define FLOOR 0xFF7F50

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;//amount of bytes taken by one row of our image. (ATTENTION : 1 pixel = 8 bytes!)
	int		endian;//Endianness means that the bytes in computer memory are read in a certain order. 
	int		ceil_color;
	int		floor_color;
}	t_img;

typedef struct s_rays
{
	int		mx;
	int		my;
	int		mp;
//	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
}	t_rays;

typedef struct s_play
{
	int		px;
	int		py;
	double	pdx; // delta x et delta y pour la rotation du player
	double	pdy;
	double	pa; // angle of the player (N/S/E/W ?)
	int		width; // A retirer plus tard
	int		height; // A retirer plus tard
	int		color;
	t_rays	ray;
}	t_play;

typedef struct s_map
{
	int	mapX;
	int	mapY;
	int	mapS;
	int	len_mapXS;
	int	len_mapYS;
//	int	map[8];
}	t_map;

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_play	play;
	t_map	map;
}	t_data;

int	mapext[] =
{
1,1,1,1,1,1,1,1,
1,0,1,0,0,0,0,1,
1,0,1,0,0,0,0,1,
1,0,1,0,0,0,0,1,
1,0,0,0,0,0,0,1,
1,0,0,0,0,1,0,1,
1,0,0,0,0,0,0,1,
1,1,1,1,1,1,1,1,
};

// typedef struct s_rect
// {
// 	int	x;
// 	int	y;
// 	int	width;
// 	int	height;
// 	int	color;
// }	t_rect;

// int render_rect(t_img *img, t_rect rect)
// {
// 	int	i;
// 	int j;

// 	i = rect.y;
// 	while (i < rect.y + rect.height)
// 	{
// 		j = rect.x;
// 		while (j < rect.x + rect.width)
// 			my_pixel_put(img, j++, i, rect.color);
// 		++i;
// 	}
// 	return (0);
// }

// int render_square(t_img *img, t_map map)
// {
// 	fill_cube(img, &map, 0, 1, BLUE_PIXEL);
// 	return (0);
// }

// int render_rect(t_img *img, t_rect rect)
// {
// 	int	i;
// 	int j;

// 	i = rect.y;
// 	while (i < rect.y + rect.height)
// 	{
// 		j = rect.x;
// 		while (j < rect.x + rect.width)
// 			my_pixel_put(img, j++, i, rect.color);
// 		++i;
// 	}
// 	return (0);
// }

// void	render_background(t_img *img, int c, int f)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < W_HEIGHT / 2)
// 	{
// 		j = 0;
// 		while (j < W_WIDTH)
// 			my_pixel_put(img, j++, i, c);
// 		++i;
// 	}
// 	i = W_HEIGHT / 2;
// 	while (i < W_HEIGHT)
// 	{
// 		j = 0;
// 		while (j < W_WIDTH)
// 			my_pixel_put(img, j++, i, f);
// 		++i;
// 	}
// }

// int	deal_escape(int key, t_data *data)
// {
// 	if (key == 65307)// || i)
// 	{
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		data->win_ptr = NULL;
// 	}
// 	return (0);
// }

// int	next_pos_is_wall(t_data *data, int next_x, int next_y)
// {
// 	int index;
	
// 	next_x = next_x / data->map.mapS;
// 	next_y = next_y / data->map.mapS;
// 	index = next_y * data->map.mapX + next_x;
// 	if (mapext[index] == 1)
// 		return (1);
// 	else
// 		return (0);
// }

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	// char	*pixel;

	// pixel = img->addr + (y * img->line_len + x * (img->bpp / 8)); // ne fct bien que si 1 pixel = 4 octets, c'est pas tjs le cas...
	// *(unsigned int*)pixel = color;

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

void	drawRays(t_play *play, t_map *map, t_rays *ray)
{
	int		r;
	int		dof;
	float	aTan;

	ray->ra = play->pa;
	r = 0;
	while (r < 1)
	{
//--- Check horizontal lines --- video 9'18//
		dof = 0;
		if (ray->ra != PI)
			aTan = - 1 / tan(ray->ra);
		else
			aTan = -1;
printf("ray->ra = [%f] | tan(ray->ra) = [%f]\n", ray->ra, tan(ray->ra));
printf("aTan = [%f]\n", aTan);
		if (ray->ra > PI) //-- player is looking down
		{
			ray->ry = (((int)(play->py) >> 6) << 6) - 0.0001;
			ray->rx = (play->py - ray->ry) * aTan + play->px;
printf(GREEN"play->py = [%d] | ray->ry = [%f] | play->px = [%d] | ray->rx = [%f]"RESET"\n", play->py, ray->ry, play->px, ray->rx);
			ray->yo = -64;
			ray->xo = -ray->yo * aTan;
		}
		if (ray->ra < PI) //-- player is looking up
		{
			ray->ry = (((int)(play->py) >> 6) << 6) + 64;
printf(PURPLE"ray->ry = [%f]"RESET"\n", ray->ry);
			ray->rx = (play->py - ray->ry) * aTan + play->px;
printf(BLUE"ray->rx = [%f]"RESET"\n", ray->rx);
			ray->yo = 64;
			ray->xo = -ray->yo * aTan;
		}
		if (ray->ra == 0 || ray->ra == PI) //-- player is looking left or right
		{
			ray->ry = play->py;
			ray->rx = play->px;
			dof = 8;
		}
printf(ORANGE"ray->rx = [%f]"RESET"\n", ray->rx);
		while (dof < 8)
		{
			// debug
//			ray->rx = -503.302240;
			// debug
			ray->mx = (int)(ray->rx)>>6;
printf(CYAN"mx = [%d] | rx = [%f]"RESET"\n", ray->mx, ray->rx);
			ray->my = (int)(ray->ry)>>6;
printf(YELLOW"my = [%d] | ry = [%f]"RESET"\n", ray->my, ray->ry);
			ray->mp = ray->my * map->mapX + ray->mx;
printf(RED"mp = [%d]"RESET"\n", ray->mp);
			if (ray->mp < map->mapX * map->mapY && mapext[ray->mp] == 1) // ray hit wall !
				dof = 8;
			else // make ray go to next wall !
			{
				ray->rx += ray->xo;
				ray->ry += ray->yo;
				dof += 1;
			}
		}
		r++;
	}
}

int render_player(t_img *img, t_play play)
{
	int	i;
	int j;

	i = play.py; // On affiche le player
	while (i < play.py + play.height)
	{
		j = play.px;
		while (j < play.px + play.width)
			my_pixel_put(img, j++, i, play.color);
		++i;
	}
	i = play.py + play.pdy * 5; // On affiche sa direction !
	while (i < play.py + play.pdy * 5 + play.height)
	{
		j = play.px + play.pdx * 5;
		while (j < play.px + play.pdx * 5 + play.width)
			my_pixel_put(img, j++, i, GREEN_PIXEL);
		++i;
	}
	i = play.ray.ry;
	while (i < play.ray.ry + play.height)
	{
		j = play.ray.rx;
		while (j < play.ray.rx + play.width)
			my_pixel_put(img, j++, i, BLUE_PIXEL);
		++i;
	}
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
//	render_square(&data->img, data->map);
//	render_background(&data->img, data->img.ceil_color, data->img.floor_color);
	render_player(&data->img, data->play);//(t_play){W_WIDTH - 100, W_HEIGHT - 100, 5, 5, GREEN_PIXEL});
	drawRays(&data->play, &data->map, &data->play.ray);
//	//render_rect(&data->img, (t_rect){W_WIDTH - 100, W_HEIGHT - 100, 100, 100, GREEN_PIXEL});
//	//render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	next_pos_is_wall(t_data *data, int sens)
{
	int index;
	int next_x;
	int next_y;

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

// 	if (sens == 1)
// 	{
// 		next_x = ((data->play.px + data->play.pdx) - (data->map.mapS / 16)) / data->map.mapS;
// 		next_y = ((data->play.py + data->play.pdy) - (data->map.mapS / 16)) / data->map.mapS;
// 		// if (data->play.pdx >= 0 && data->play.pdy >= 0)
// 		// 	index = (next_y * data->map.mapX + next_x) - 1;
// 		// if (data->play.pdx >= 0 && data->play.pdy < 0)
// 		// 	index = next_y * data->map.mapX + next_x;	
// 		// if (data->play.pdx < 0 && data->play.pdy >= 0)
// 		// 	index = next_y * data->map.mapX + next_x;
// 		// if (data->play.pdx < 0 && data->play.pdy < 0)
// 		index = next_y * data->map.mapX + next_x;
// printf(PURPLE"index = [%d] | pdx = [%f] | pdy = [%f]"RESET"\n", index, data->play.pdx, data->play.pdy);
// 	}
// 	else
// 	{
// 		next_x = ((data->play.px - data->play.pdx) + (data->map.mapS / 16)) / data->map.mapS;
// 		next_y = ((data->play.py - data->play.pdy) + (data->map.mapS / 16)) / data->map.mapS;
// 		index = (next_y * data->map.mapX + next_x);
// printf(YELLOW"index = [%d]"RESET"\n", index);
// 	}
	index = next_y * data->map.mapX + next_x;
printf(GREEN"index = [%d] | map = [%d]"RESET"\n", index, mapext[index]);
	if (mapext[index] == 1)
		return (1);
	else
		return (0);
}

int	deal_key(int key, t_data *data)
{
//	if (key == 119 && (data->play.py - 5) >= 0 && !next_pos_is_wall(data, data->play.px, data->play.py - 5 - data->map.mapS / 4))// && mapext[data->play.py - 1] != 1) // w mapext[y * map.mapX + x]
	// if (key == 119 && !next_pos_is_wall(data, ((data->play.px + data->play.pdx) - data->map.mapS / 16), ((data->play.py + data->play.pdy) - data->map.mapS / 16)))
	if (key == 119 && !next_pos_is_wall(data, 1))//, ((data->play.px + data->play.pdx) - data->map.mapS / 16), ((data->play.py + data->play.pdy) - data->map.mapS / 16)))
	{
printf("W | next = [%d]\n", next_pos_is_wall(data, 1));
//		data->play.py -= 5;
		data->play.px += data->play.pdx;
		data->play.py += data->play.pdy;
	}
//	if (key == 115 && (data->play.py + 5) < data->map.len_mapYS && !next_pos_is_wall(data, data->play.px, data->play.py + 5)) // s
//	if (key == 115 && !next_pos_is_wall(data, ((data->play.px - data->play.pdx) + data->map.mapS / 16), ((data->play.py - data->play.pdy) + data->map.mapS / 16))) // s
	if (key == 115 && !next_pos_is_wall(data, 0))//((data->play.px - data->play.pdx) + data->map.mapS / 16), ((data->play.py - data->play.pdy) + data->map.mapS / 16))) // s
	{
printf("S\n");
//		data->play.py += 5;
		data->play.px -= data->play.pdx;
		data->play.py -= data->play.pdy;
	}
//	if (key == 97 && (data->play.px - 5) >= 0 && !next_pos_is_wall(data, data->play.px - 5 - data->map.mapS / 4, data->play.py)) // a
	if (key == 97)// && !next_pos_is_wall(data, data->play.px - 5 - data->map.mapS / 4, data->play.py)) // a
	{
printf("A\n");
//		data->play.px -= 5;
		data->play.pa -= 0.1;
		if (data->play.pa < 0)
			data->play.pa += 2 * PI;
		data->play.pdx = cos(data->play.pa) * 5;
		data->play.pdy = sin(data->play.pa) * 5;	
	}
//	if (key == 100)// && (data->play.px + 5) < data->map.len_mapXS && !next_pos_is_wall(data, data->play.px + 5 + data->map.mapS / 4, data->play.py)) // d
	if (key == 100)
	{
printf("D\n");
//		data->play.px += 5;
		data->play.pa += 0.1;
		if (data->play.pa > 2 * PI)
			data->play.pa -= 2 * PI;
		data->play.pdx = cos(data->play.pa) * 5;
		data->play.pdy = sin(data->play.pa) * 5;	
	}
	if (key == 65307)// || i)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	// // 	ft_close(data);
	return (0);
}



int	main(void)
{
	t_data	data;

//---- initialisations de donnees ----//
	data.img.ceil_color = 0xFFFF;
	data.img.floor_color = 0xFF7F50;

	data.play.px = 300;
	data.play.py = 300;
	data.play.width = 5; // A retirer plus tard
	data.play.height = 5; // A retirer plus tard
	data.play.color = 0x00FF0000;
	data.play.pa = PI;
	data.play.pdx = cos(data.play.pa) * 5;
	data.play.pdy = sin(data.play.pa) * 5;

	data.map.mapX = 8;
	data.map.mapY = 8;
	data.map.mapS = 64;
	data.map.len_mapXS = data.map.mapX * data.map.mapS;
	data.map.len_mapYS = data.map.mapY * data.map.mapS;
//	data.map.map = mapext;
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
	// };

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	//data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "Cub3D_test");
//	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map.mapX * 64, data.map.mapY * 64, "Cub3D_test");
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map.len_mapXS, data.map.len_mapYS, "Cub3D_test");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (1);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, data.map.len_mapXS, data.map.len_mapYS);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);
//	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.mlx_img, 0, 0);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
//	mlx_mouse_hook(data.win_ptr, deal_mouse, &data); // si un jour on veut utiliser la souris
/* ATTENTION : différence entre mlx_key_hook et mlx_hook ! mlx_key_hook : la fct ne s'active que
lorsque le bouton est relaché ! mlx_hook : la fct s'active lorsque le bouton est pressé !!!*/
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &deal_key, &data); // for escape and quit
	// mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &deal_key, &data); // for movements

//	mlx_key_hook(data.win_ptr, &deal_key, &data); // for movements


//	mlx_hook(img->img, 17, 1L << 17, ft_close, data);
	mlx_loop(data.mlx_ptr);


//	mlx_destroy_window(data.mlx_ptr, data.win_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}


// https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx