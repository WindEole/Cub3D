/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:14:16 by iderighe          #+#    #+#             */
/*   Updated: 2022/09/03 16:25:31 by acoinus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# undef __STRICT_ANSI__ // Pour que VsCode reconnaisse M_PI !!
# define _USE_MATH_DEFINES

# include <math.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "X11/X.h"
# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define ORANGE "\033[38;2;255;165;0m"
# define RESET "\033[0m"

# define W_WIDTH 1219//1381//1544//1625//1706//
# define W_HEIGHT 914//1036//1158//1219//1280//

# define GREEN_PIXEL 0x33FF66
# define RED_PIXEL 0xCC0033
# define BLUE_PIXEL 0x0033CC
# define YELLOW_PIXEL 0xFFFF66
# define PINK_PIXEL 0xFF33FF
# define ORANGE_PIXEL 0xFF6633

# define WHITE_PIXEL 0xFFFFFF
# define GRAY_PIXEL 0x808080
# define BLACK_PIXEL 0x000000

# define CUBE_SIDE 64
# define SPEED 1.5
# define FOV 60

/*-------------------------   structures   -----------------------------------*/

typedef struct s_rays
{
	int		mx;
	int		my;
	int		mp;
	double	rx;
	double	ry;
	double	ra;
	double	xo;
	double	yo;
}	t_rays;

typedef struct s_play
{
	int		px;
	int		py;
	int		pos_init;
	double	pdx;
	double	pdy;
	double	pa;
	int		dof;
	int		end_dof;
	double	dist_h;
	double	dhx;
	double	dhy;
	double	dist_v;
	double	dvx;
	double	dvy;
	double	dist_final;
	int		width;
	int		height;
	char	texture;
	t_rays	ray;
}	t_play;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		r;
	int		l;
}	t_keys;

typedef struct s_map
{
	int		x;
	int		y;
	int		xy;
	int		len_x;
	int		len_y;
}	t_map;

typedef struct s_tex
{
	char	*f;
	char	*c;
	t_img	*ea;
	t_img	*we;
	t_img	*so;
	t_img	*no;
	t_img	*fl;
	t_img	*ce;
	float	ty;
	float	tx;
	float	ty_off;
}	t_tex;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		fd;
	int		*mapext;
	float	scale;
	int		tex_switch;
	char	*txtr[5];
	int		tx[4];
	int		f;
	int		c;
	char	*s_cub;
	t_img	*rendu;
	t_play	play;
	t_keys	key;
	t_map	map;
	t_tex	tex;
}	t_data;

/*-----------------------   prototypes parsing   -----------------------------*/

//--- p1_main.c ---//

int		ft_free(t_data *data, int ret);//, int niv);

//--- p2_pars.c ---//

int		valid_tex_path(t_data *data, char *s, int i);
int		set_texture(char *s, char c, t_data *data);
int		pars(t_data *data);

//--- p3_elmt_checker.c ---//

int		elmt_checker(int i, char *line, t_data *data, int x);

//--- p4_map_checker.c ---//

int		map_checker(char *s, t_data *data, int x);

//--- p5_wall_checker.c ---//

int		p_checker(t_data *data, int i);

//--- p6_utils.c ---//

char	*ft_strdup_n(const char *s, int n);
int		ft_strlen_i(int *str);
int		ft_isdigit_cub(char *s);
int		ft_error(int err, int fd);

//--- p7_strjoin_map.c ---//

int		ft_strjoin_map(t_data *data, char *s2, int i, int j);

/*-----------------------   prototypes graphical   ---------------------------*/

//--- g1_graphical.c ---//

void	my_pixel_put(t_img *img, int x, int y, int color);
int		ft_close(t_data *data);
int		graphical(t_data *data);

//--- g2_init.c ---//

int		init_texture(t_data *data, int s);
void	init_data(t_data *data);

//--- g3_movekey.c ---//

void	deal_key(t_data *data);
int		button_released(int key, t_data *data);
int		button_pressed(int key, t_data *data);

//--- g4_movement.c ---//

void	move_right(t_data *data);
void	move_left(t_data *data);
void	move_forward(t_data *data);
void	move_backward(t_data *data);

//--- g5_raycasting1.c ---//

void	raycasting(t_play *play, t_rays *ray, t_data *data);

//--- g5_raycasting2.c ---//

void	define_dist_final(t_play *play, t_rays *ray);
void	define_dist(t_play *play, t_rays *ray, t_data *data, int hv);

//--- g6_game1.c ---//

int		define_color(char t, t_tex *tex);
void	draw_3d(t_play *play, t_img *img, int r, t_data *data);
void	render_background(t_img *rendu, int c, int f);

//--- g6_game2.c ---//

int		find(float x, float y, t_img *tex);
int		shading(int c, t_data *data, int end_line, float pow);
void	draw_floor_ceiling(t_data *data, t_img *img, int line_end, int r);

//--- g7_minimap.c ---//

void	draw_ray_0(t_data *data, double a, double dist, int color);
int		render_player(t_img *img, t_play play, t_data *data);
int		render_map(t_map map, t_data *data);

#endif
