/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:18:03 by iderighe          #+#    #+#             */
/*   Updated: 2021/12/08 16:03:21 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"





int	ft_close(t_adm **adm)
{
	void	**p;
	int		i;

	p = adm[0]->p;
	i = 1;
	printf(RESET"\n");
	if (p[0])
	{
		while (++i < 7)
			if (p[i])
				mlx_destroy_image(p[0], p[i]);
		if (p[1])
			mlx_destroy_window(p[0], p[1]);
		mlx_destroy_display(p[0]);
		free(p[0]);
	}
	ft_free_allist(adm, adm[0]->y, NULL);
	exit (0);
	return (0);
}

int	deal_key(int key, t_adm **adm)
{
	void	**p;
	int		i;

	p = adm[0]->p;
	i = 0;
	if (key == 119)
		i += ft_vert(adm, p, 1);
	if (key == 115)
		i += ft_vert(adm, p, -1);
	if (key == 97)
		i += ft_hori(adm, p, 1);
	if (key == 100)
		i += ft_hori(adm, p, -1);
	if (key == 65307 || i)
		ft_close(adm);
	return (0);
}

void	ft_player_init(t_adm **adm, int x, int y, int color)
{
	char	*dst;
	int		offset;
printf(RED"graphical.c/ft_player_init | adm[0]->len = [%d] | adm[0]->bpp = [%d]"RESET"\n", adm[0]->len, adm[0]->bpp);
	offset = (y * adm[0]->len) + (x * (adm[0]->bpp / 8));
printf(RED"graphical.c/ft_player_init | offset = [%d]"RESET"\n", offset);
	dst = adm[0]->addr + offset;
	*(unsigned int *)dst = color;
}

void	ft_complete_img(t_adm **adm, void **p, int y)
{
	int		i;
	int		s_x;
	t_dll	*now;

	i = -1;
	while (++i < y)
	{
		now = adm[i]->head;
		s_x = 0;
		while (now != NULL)
		{
			if (now->c == '1')
				mlx_put_image_to_window(p[0], p[1], p[2], s_x, (i * DEF));
			// else if (now->c == 'E')
			// 	mlx_put_image_to_window(p[0], p[1], p[4], s_x, (i * DEF));
			// else if (now->c == 'C')
			// 	mlx_put_image_to_window(p[0], p[1], p[5], s_x, (i * DEF));
			// else if (now->c == 'P')
			// 	mlx_put_image_to_window(p[0], p[1], p[6], s_x, (i * DEF));
			else if (now->c == 'N' || now->c == 'S' || now->c == 'E' || now->c == 'W')
			{
printf(PURPLE"s_x = [%d] | now->x = [%d] | now->y = [%d]"RESET"\n", s_x, now->x, now->y);
				ft_player_init(&adm[0], now->x, now->y, 0x00FF0000);
				// enregistrer la position px/py du player
			}
			// else
			// 	mlx_put_image_to_window(p[0], p[1], p[3], s_x, (i * DEF));
			s_x += DEF;
			now = now->r;
		}
	}
}

void	ft_init_tex(void **p)
{
	int	def;

	def = DEF;
	p[2] = mlx_xpm_file_to_image(p[0], "./Tex/Wal.xpm", &def, &def);
	p[3] = mlx_xpm_file_to_image(p[0], "./Tex/Sol.xpm", &def, &def);
	p[4] = mlx_xpm_file_to_image(p[0], "./Tex/Exi.xpm", &def, &def);
	p[5] = mlx_xpm_file_to_image(p[0], "./Tex/Col.xpm", &def, &def);
	p[6] = mlx_xpm_file_to_image(p[0], "./Tex/Pla.xpm", &def, &def);
}

int	ft_graphical(t_adm **adm, int x, int y)
{
	adm[0]->p[0] = mlx_init();
	if (adm[0]->p[0] == NULL)
		return (ft_error("Error\n- no connection to graphical serve !", 0));
	ft_init_tex(adm[0]->p);
	if (adm[0]->p[2] == NULL || adm[0]->p[3] == NULL || adm[0]->p[4] == NULL
		|| adm[0]->p[5] == NULL || adm[0]->p[6] == NULL)
		return (ft_close(adm));
	adm[0]->p[1] = mlx_new_window(adm[0]->p[0], (DEF * x), (DEF * y), "cub3D");
	if (adm[0]->p[1] == NULL)
		return (ft_error("Error\n- impossible to create window", 0));
//
	adm[0]->img = mlx_new_image(adm[0]->p[0], (DEF * x), (DEF * y));
	if (adm[0]->img == NULL)
		return (ft_error("Error\n- impossible to create general image", 0));
	adm[0]->addr = mlx_get_data_addr(adm[0]->img, &adm[0]->bpp, &adm[0]->len, &adm[0]->endian);
	if (adm[0]->addr == NULL)
		return (ft_error("Error\n- impossible to retrieve image adress", 0));
//
	ft_complete_img(adm, adm[0]->p, y);
	adm[0]->op = 0;
	adm[0]->e = 0;
	adm[0]->te = 0;
	printf(CYAN"Nombre de coups :\n");
	mlx_key_hook(adm[0]->p[1], deal_key, adm);
	mlx_hook(adm[0]->p[1], 17, 1L << 17, ft_close, adm);
	mlx_loop(adm[0]->p[0]);
	printf(CYAN"%d"RESET"\n", adm[0]->op);
	return (TRUE);
}

///////////////////////////////////////////////////////////////////
/*
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp; //bits_per_pixel
	int		len; // line_length ATTENTION : != de la largeur de fenetre ! donc il faut calculer offset
	int		endian;
}	t_data;

void	ft_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->len) + (x * (data->bpp / 8));
	dst = data->addr + offset;
	*(unsigned int *)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init(); // ici mlx = adm[0]->p[0]
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World"); //OK !!! ici mlx_win = adm[0]->p[1]
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.len, &img.endian); // Now we have the image address
	ft_pixel_put(&img, 5, 5, 0x00FF0000); // 0x... = representation of ARGB(0,255,0,0)
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}*/

///////////////////////////////////////////////////////////////////