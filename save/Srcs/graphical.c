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
				mlx_put_image_to_window(p[0], p[1], p[2], s_x, (i * PI));
			// else if (now->c == 'E')
			// 	mlx_put_image_to_window(p[0], p[1], p[4], s_x, (i * PI));
			// else if (now->c == 'C')
			// 	mlx_put_image_to_window(p[0], p[1], p[5], s_x, (i * PI));
			// else if (now->c == 'P')
			// 	mlx_put_image_to_window(p[0], p[1], p[6], s_x, (i * PI));
			else if (now->c == 'N' || now->c == 'S' || now->c == 'E' || now->c == 'W')
			{
				// enregistrer la position px/py du player
			}
			// else
			// 	mlx_put_image_to_window(p[0], p[1], p[3], s_x, (i * PI));
			s_x += PI;
			now = now->r;
		}
	}
}

void	ft_init_tex(void **p)
{
	int	pi;

	pi = PI;
	p[2] = mlx_xpm_file_to_image(p[0], "./Tex/Wal.xpm", &pi, &pi);
	p[3] = mlx_xpm_file_to_image(p[0], "./Tex/Sol.xpm", &pi, &pi);
	p[4] = mlx_xpm_file_to_image(p[0], "./Tex/Exi.xpm", &pi, &pi);
	p[5] = mlx_xpm_file_to_image(p[0], "./Tex/Col.xpm", &pi, &pi);
	p[6] = mlx_xpm_file_to_image(p[0], "./Tex/Pla.xpm", &pi, &pi);
}

// int	ft_graphical(t_adm **adm, int x, int y)
// {
// 	adm[0]->p[0] = mlx_init();
// 	if (adm[0]->p[0] == NULL)
// 		return (ft_error("Error\n- no connection to graphical serve !", 0));
// 	ft_init_tex(adm[0]->p);
// 	if (adm[0]->p[2] == NULL || adm[0]->p[3] == NULL || adm[0]->p[4] == NULL
// 		|| adm[0]->p[5] == NULL || adm[0]->p[6] == NULL)
// 		return (ft_close(adm));
// 	adm[0]->p[1] = mlx_new_window(adm[0]->p[0], (PI * x), (PI * y), "so_long");
// 	if (adm[0]->p[1] == NULL)
// 		return (ft_error("Error\n- impossible to create window", 0));
// 	ft_complete_img(adm, adm[0]->p, y);
// 	adm[0]->op = 0;
// 	adm[0]->e = 0;
// 	adm[0]->te = 0;
// 	printf(CYAN"Nombre de coups :\n");
// 	mlx_key_hook(adm[0]->p[1], deal_key, adm);
// 	mlx_hook(adm[0]->p[1], 17, 1L << 17, ft_close, adm);
// 	mlx_loop(adm[0]->p[0]);
// 	printf(CYAN"%d"RESET"\n", adm[0]->op);
// 	return (TRUE);
// }

void	ft_my_mlx_pixel_put(t_adm *adm, int x, int y, int color) // ajout cub
{
	char	*dst;

	dst = data->addr + (y * adm->)
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
	adm[0]->p[1] = mlx_new_window(adm[0]->p[0], (PI * x), (PI * y), "so_long");
	if (adm[0]->p[1] == NULL)
		return (ft_error("Error\n- impossible to create window", 0));
	ft_complete_img(adm, adm[0]->p, y);
	adm[0]->op = 0;
	adm[0]->e = 0;
	adm[0]->te = 0;
	printf(CYAN"Nombre de coups :\n");
	mlx_key_hook(adm[0]->p[1], deal_key, adm);
	mlx_hook(adm[0]->p[1], 17, 1L << 17, ft_close, adm);
	mlx_loop(adm[0]->p[0]);
//
	// adm[0]->addr = mlx_get_data_addr(adm)
	// ft_my_mlx_pixel_put(adm[0]->p[0], x, y, adm[0]->color);
//
	printf(CYAN"%d"RESET"\n", adm[0]->op);
	return (TRUE);
}
