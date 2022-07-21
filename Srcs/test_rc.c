#include "cub3d.h"
#include "X11/X.h"

# define W_WIDTH 1010//512
# define W_HEIGHT 512

# define GREEN_PIXEL 0x33FF66
# define RED_PIXEL 0xCC0033
# define BLUE_PIXEL 0x0033CC
# define YELLOW_PIXEL 0xFFFF66
# define PINK_PIXEL 0xFF33FF
# define ORANGE_PIXEL 0xFF6633

# define WHITE_PIXEL 0xFFFFFF
# define GRAY_PIXEL 0x808080
# define BLACK_PIXEL 0x000000

# define CEILING 0xFFFF
# define FLOOR 0xFF7F50


// typedef union u_mlx_color
// {
// 	struct
// 	{
// 		uint8_t	b;
// 		uint8_t	g;
// 		uint8_t	r;
// 		uint8_t	a;
// 	};
// 	uint32_t	argb;
// }	t_mlx_color;

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
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	int 	ray_color;
}	t_rays;

typedef struct s_play
{
	int		px;
	int		py;
	double	pdx; // delta x et delta y pour la rotation du player
	double	pdy;
	double	pa; // angle of the player (N/S/E/W ?)
	float	dist_H;
	float	dhx;
	float	dhy;
	float	dist_V;
	float	dvx;
	float	dvy;
	float	dist_final;
	int		width; // A retirer plus tard
	int		height; // A retirer plus tard
	int		color;
//	t_line	line;
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
//	char	*pixel;


	// pixel = img->addr + (y * img->line_len + x * (img->bpp / 8)); // ne fct bien que si 1 pixel = 4 octets, c'est pas tjs le cas...
	// *(unsigned int*)pixel = color;

	char	*pixel;
	int		i;

	if (x > W_WIDTH || y > W_HEIGHT)
	{
		printf("Ça a envoyé de la merde !\n");
		printf(CYAN"x = %d | y = %d"RESET"\n", x, y);
		return;
	}

	i = img->bpp - 8;
//printf(CYAN"img->bpp = [%d] | i = [%d]"RESET"\n", img->bpp, i);
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
	while (i < 320 / 2)
	{
		j = 530;
		while (j < W_WIDTH)
			my_pixel_put(img, j++, i, c);
		++i;
	}
	i = 320 / 2;
	while (i < 320)
	{
		j = 530;
		while (j < W_WIDTH)
			my_pixel_put(img, j++, i, f);
		++i;
	}
}

// int render_line(t_img *img, t_line line)
// {
// 	int	i;
// 	int j;

// 	i = line.yA;
// 	while (i < line.yB)
// 	{
// 		j = line.xA;
// 		while (j < line.xB)
// 		{
// 			if (i == line.a * j + line.b)
// 				my_pixel_put(img, j, i, line.color);
// 			j++;			
// 		}
// 		++i;
// 	}
// 	return (0);
// }

// int draw_line(t_img *img, t_play play)
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
// 	return (0);
// }

void	draw_3D(t_play *play, t_map *map, t_img *img, int r)
{
	int		i;
	int		j;
	float	line_origin;
	float	fish_eye;
	float	lineH;

	fish_eye = play->pa - play->ray.ra;
	if (fish_eye < 0)
		fish_eye += 2 * M_PI;
	if (fish_eye > 2 * M_PI)
		fish_eye -= 2 * M_PI;
	play->dist_final = play->dist_final * cos(fish_eye);
	lineH = map->mapS * 320 / play->dist_final; // line height !
	if (lineH > 320)
		lineH = 320;
	line_origin = 160 - lineH / 2;
	i = line_origin;
	while (i < lineH + line_origin)
	{
		j = r * 8 + 530;

		while (j < (r * 8 + 530) + 8)
		{
// printf(BLUE"j = %d"RESET"\n", j);			
			my_pixel_put(img, j++, i, play->ray.ray_color);
		}
		++i;
	}
}

// int draw_line(t_img *img, float line, int r)
// {
// 	int		i;
// 	int		j;
// 	float	line_origin;

// //	play.line.a = ((play.py - play.pdy)/(play.px - play.pdx));
// //	play.line.b = line;
// //printf(GREEN"px = [%d] | py = [%d] | pdx = [%f] | pdy = [%f]"RESET"\n", play.px, play.py, play.pdx, play.pdy);	
// //printf(RED"a = [%f] | b = [%f]"RESET"\n", play.line.a, play.line.b);
// 	line_origin = 160 - line / 2;
// 	i = line_origin;
// 	while (i < line + line_origin)
// 	{
// 		j = r * 8 + 530;
// 		while (j < (r * 8 + 530) + 8)
// 		{
// //		printf(BLUE"ici ?"RESET"\n");
// //			if (i == play.line.a * j + play.line.b)
// //			if (i == line)
// 			my_pixel_put(img, j++, i, GREEN_PIXEL);
// //			j++;			
// 		}
// 		++i;
// 	}
// 	return (0);
// }

float	calcul_dist(float px, float py, float rx, float ry)
{
	return (sqrt((rx - px) * (rx - px) + (ry - py) * (ry - py)));
}

void	drawRays(t_play *play, t_map *map, t_rays *ray, t_img *img)
{
	int		r; // r = nb de rayons lancés par le player !
	int		dof;
	float	aTan;
	float	nTan;

//	ray->ra = play->pa; // ra = raised angle
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
printf(ORANGE"//-----------------------------------------------------------------------//"RESET"\n");
printf(BLUE"ray->ra = %f"RESET"\n", ray->ra);
	r = 0;
	while (r < 60) 
	{
//--- Check horizontal lines --- video 9'18//
		dof = 0;
		aTan = -1 / tan(ray->ra);
		if (ray->ra == 0 || ray->ra == M_PI || ray->ra == 2 * M_PI) //-- player is looking left or right
		{
//printf(YELLOW"ra = [%f] | player is looking left or right !"RESET"\n", ray->ra);
			ray->ry = play->py;
			ray->rx = play->px;
			dof = 8;
		}
		else if (ray->ra < M_PI) //-- player is looking up 
		{
//printf(RED"ra = [%f] | player is looking up !"RESET"\n", ray->ra);
			if (((((int)(play->py) >> 6) << 6) - 0.0001) < map->len_mapYS && ((((int)(play->py) >> 6) << 6) - 0.0001) > 0)
				ray->ry = (((int)(play->py) >> 6) << 6) - 0.0001;
			if (((play->py - ray->ry) * aTan + play->px) < map->len_mapXS && ((play->py - ray->ry) * aTan + play->px) > 0)
				ray->rx = (play->py - ray->ry) * aTan + play->px;
			ray->yo = -64;
			ray->xo = -ray->yo * aTan;
printf(RED"look up : ray->rx = %f | ray->ry = %f"RESET"\n", ray->rx, ray->ry);
		}
		else if (ray->ra > M_PI) //-- player is looking down
		{
//printf(GREEN"ra = [%f] | player is looking down!"RESET"\n", ray->ra);
			if (((((int)(play->py) >> 6) << 6) + 64) < map->len_mapYS && ((((int)(play->py) >> 6) << 6) + 64) > 0)
				ray->ry = (((int)(play->py) >> 6) << 6) + 64;
			if (((play->py - ray->ry) * aTan + play->px) < map->len_mapXS && ((play->py - ray->ry) * aTan + play->px) > 0)
				ray->rx = (play->py - ray->ry) * aTan + play->px;
			ray->yo = 64;
			ray->xo = -ray->yo * aTan;
printf(GREEN"look down : ray->rx = %f | ray->ry = %f"RESET"\n", ray->rx, ray->ry);
		}
		while (dof < 8)
		{
			if (ray->rx > 0)
				if (ray->rx < map->len_mapXS)
					ray->mx = (int)(ray->rx)>>6;
			if (ray->ry > 0)
				if (ray->ry < map->len_mapYS)
					ray->my = (int)(ray->ry)>>6;
			ray->mp = ray->my * map->mapX + ray->mx;
			if (ray->mp > 0 && ray->mp < map->mapS && mapext[ray->mp] == 1) // ray hit wall !
			{
				play->dhx = ray->rx;
				play->dhy = ray->ry;
				play->dist_H = calcul_dist(play->px, play->py, play->dhx, play->dhy);
//printf(GREEN"rx = %f | ry = %f | distH = %f"RESET"\n", ray->rx, ray->ry, play->dist_H);
				dof = 8;
			}
			else // make ray go to next wall !
			{
//printf(ORANGE"ra = %f | rx = %f | mx = %d | ry = %f | my = %d | ray->mp = [%d]"RESET"\n", ray->ra, ray->rx, ray->mx, ray->ry, ray->my, ray->mp);
				if (ray->rx < map->len_mapXS && (ray->rx + ray->xo) < map->len_mapXS && ray->rx > 0)
					ray->rx += ray->xo;
				if (ray->ry < map->len_mapYS && (ray->ry + ray->yo) < map->len_mapYS && ray->ry > 0)				
					ray->ry += ray->yo;
				dof += 1;
			}
		}
// //---dessinons les rayons horizontaux ! ---//
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
// --- Check vertical lines --- video 10'25// P2 = PI/2 | P3 = 3 * PI/2
		dof = 0;
		nTan = -tan(ray->ra);
		if (ray->ra == 0 || ray->ra == M_PI || ray->ra == 2 * M_PI) //-- player is looking up or down
		{
//printf(ORANGE"ra = [%f] | player is looking up or down !"RESET"\n", ray->ra);
			ray->ry = play->py;
			ray->rx = play->px;
			dof = 8;
		}
		else if (ray->ra < (M_PI / 2) || ray->ra > (3 * M_PI / 2)) //-- player is looking right
		{
//printf(PURPLE"ra = [%f] | player is looking left !"RESET"\n", ray->ra);
			if (((((int)(play->px) >> 6) << 6) - 0.0001) < map->len_mapYS && ((((int)(play->px) >> 6) << 6) - 0.0001) > 0)
				ray->rx = (((int)(play->px) >> 6) << 6) - 0.0001;
			if (((play->px - ray->rx) * nTan + play->py) < map->len_mapXS && ((play->px - ray->rx) * nTan + play->py) > 0)
				ray->ry = (play->px - ray->rx) * nTan + play->py;
			ray->xo = -64;
			ray->yo = -ray->xo * nTan;
printf(PURPLE"look right : ray->rx = %f | ray->ry = %f"RESET"\n", ray->rx, ray->ry);
		}
		else if (ray->ra > (M_PI / 2) && ray->ra < (3 * M_PI / 2)) //-- player is looking left
		{
//printf(CYAN"look left : ray->rx = %f | play->px = %d | ray->ry = %f | play->py = %d"RESET"\n", ray->rx, play->px, ray->ry, play->py);
			if (((((int)(play->px) >> 6) << 6) + 64) < map->len_mapYS && ((((int)(play->px) >> 6) << 6) + 64) > 0)
				ray->rx = (((int)(play->px) >> 6) << 6) + 64;
			if (((play->px - ray->rx) * nTan + play->py) < map->len_mapXS && ((play->px - ray->rx) * nTan + play->py) > 0)
				ray->ry = (play->px - ray->rx) * nTan + play->py;
			ray->xo = 64;
			ray->yo = -ray->xo * nTan;
printf(CYAN"look left : ray->rx = %f | play->px = %d | ray->ry = %f | play->py = %d"RESET"\n", ray->rx, play->px, ray->ry, play->py);
		}
		while (dof < 8)
		{
			if (ray->rx > 0)
				if (ray->rx < map->len_mapXS)
					ray->mx = (int)(ray->rx)>>6;
			if (ray->ry > 0)
				if (ray->ry < map->len_mapYS)
					ray->my = (int)(ray->ry)>>6;
			ray->mp = ray->my * map->mapX + ray->mx;
// printf(YELLOW"rx = %f | mx = %d | ry = %f | my = %d"RESET"\n", ray->rx, ray->mx, ray->ry, ray->my);
// printf(ORANGE"ray->mp = [%d]"RESET"\n", ray->mp);
// printf(BLUE"dof = [%d]"RESET"\n", dof);
			if (ray->mp > 0 && ray->mp < map->mapS && mapext[ray->mp] == 1) // ray hit wall !
			{
				play->dvx = ray->rx;
				play->dvy = ray->ry;
				play->dist_V = calcul_dist(play->px, play->py, play->dvx, play->dvy);
				dof = 8;
			}
			else // make ray go to next wall !
			{
//printf(BLUE"ra = %f | rx = %f | mx = %d | ry = %f | my = %d | ray->mp = [%d]"RESET"\n", ray->ra, ray->rx, ray->mx, ray->ry, ray->my, ray->mp);
				if (ray->rx < map->len_mapXS && (ray->rx + ray->xo) < map->len_mapXS && ray->rx > 0)
					ray->rx += ray->xo;
				if (ray->ry < map->len_mapYS && (ray->ry + ray->yo) < map->len_mapYS && ray->ry > 0)				
					ray->ry += ray->yo;
				dof += 1;
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
		draw_3D(play, map, img, r);
		ray->ra += M_PI / 180;
		if (ray->ra < 0)
			ray->ra += 2 * M_PI;
		if (ray->ra > 2 * M_PI)
			ray->ra -= 2 * M_PI;
printf(ORANGE"//---------------------------------------------------------------------//"RESET"\n");
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
	// i = play.py + play.pdy * 5; // On affiche sa direction !
	// while (i < play.py + play.pdy * 5 + play.height)
	// {
	// 	j = play.px + play.pdx * 5;
	// 	while (j < play.px + play.pdx * 5 + play.width)
	// 		my_pixel_put(img, j++, i, GREEN_PIXEL);
	// 	++i;
	// }
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
	while (y < map.mapY)// && y < W_HEIGHT)
	{
		x = 0;
		while (x < map.mapX)// && x < W_WIDTH)
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
	render_background(&data->img, data->img.ceil_color, data->img.floor_color);
	render_player(&data->img, data->play);//(t_play){W_WIDTH - 100, W_HEIGHT - 100, 5, 5, GREEN_PIXEL});
	drawRays(&data->play, &data->map, &data->play.ray, &data->img);
	//render_rect(&data->img, (t_rect){W_WIDTH - 100, W_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	//render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
//	render_line(&data->img, (t_line){10, 10, 55, 100, ((10-100)/(10-55)), ((100*(10-55)-55*(10-100))/(10-55)), RED_PIXEL});
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
	index = next_y * data->map.mapX + next_x;
	if (mapext[index] == 1)
		return (1);
	else
		return (0);
}

int	deal_key(int key, t_data *data)
{
//	if (key == 119 && !next_pos_is_wall(data, 1))
	if (key == 115 && !next_pos_is_wall(data, 1))
	{
printf("S\n");
		data->play.px += data->play.pdx;
		data->play.py += data->play.pdy;
	}
//	if (key == 115 && !next_pos_is_wall(data, 0))
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

//---- initialisations de donnees ----//
	data.img.ceil_color = 0xFFFF;
	data.img.floor_color = 0xFF7F50;

	data.play.px = 300;
	data.play.py = 300;
	data.play.width = 5; // A retirer plus tard
	data.play.height = 5; // A retirer plus tard
	data.play.color = 0x00FF0000;
	data.play.pa = M_PI / 2;
	data.play.pdx = cos(data.play.pa);// * 5;
	data.play.pdy = sin(data.play.pa);// * 5;
	data.play.dist_H = 1000000;
	data.play.dist_V = 1000000;

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
//	data.win_ptr = mlx_new_window(data.mlx_ptr, data.map.len_mapXS, data.map.len_mapYS, "Cub3D_test");
	data.win_ptr = mlx_new_window(data.mlx_ptr, W_WIDTH, W_HEIGHT, "Cub3D_test");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (1);
	}

//	data.img.mlx_img = mlx_new_image(data.mlx_ptr, data.map.len_mapXS, data.map.len_mapYS);
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, W_WIDTH, W_HEIGHT);
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

// video 11'35 tracer le plus petit des rayons (hit Vertical ou hit Horizontal)
// https://aurelienbrabant.fr/blog/pixel-drawing-with-the-minilibx