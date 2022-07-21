/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:12:58 by iderighe          #+#    #+#             */
/*   Updated: 2021/12/13 11:00:08 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
#include "X11/X.h"
# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define TRUE 1
# define FALSE 0
# define DEF 64
//# define BUFFER_SIZE 8

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define ORANGE "\033[38;2;255;165;0m"
# define RESET "\033[0m"

# define W_WIDTH 2030//1010//512
# define W_HEIGHT 900//512

# define GREEN_PIXEL 0x33FF66
# define RED_PIXEL 0xCC0033
# define BLUE_PIXEL 0x0033CC
# define YELLOW_PIXEL 0xFFFF66
# define PINK_PIXEL 0xFF33FF
# define ORANGE_PIXEL 0xFF6633

# define WHITE_PIXEL 0xFFFFFF
# define GRAY_PIXEL 0x808080
# define BLACK_PIXEL 0x000000

# define CEILING 0xE699FFFF
# define FLOOR 0xE6CCFFCC

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
	int		mx; // position x sur map de l'impact du rayon
	int		my; // position y sur map de l'impact du rayon
	int		mp; // numero du carré de la map de l'impact du rayon
	float	rx; // coordonnée x de l'impact du rayon sur une intersection
	float	ry; // coordonnée y de l'impact du rayon sur une intersection
	float	ra; // angle du rayon
	float	xo; // offset sur x
	float	yo; // offset sur y
	int 	ray_color;
}	t_rays;

typedef struct s_play
{
	int		px;
	int		py;
	double	pdx; // delta x pour la rotation du player
	double	pdy; // delta y pour la rotation du player
	double	pa; // angle of the player (N/S/E/W ?)
	int		dof;
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

#endif