/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g1_graphical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:54:16 by iderighe          #+#    #+#             */
/*   Updated: 2022/08/18 17:54:21 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	((int *)img->data)[y * img->width + x] = color;
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	deal_key(data);
	raycasting(&data->play, &data->play.ray, data);
	render_map(data->map, data);
	render_player(data->rendu, data->play, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->rendu, 0, 0);
	return (0);
}

int	ft_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}

void	destroy_all(t_data *data, int n, int i)
{
	if (data->rendu)
		mlx_destroy_image(data->mlx_ptr, data->rendu);
	if (data->tex.ea)
		mlx_destroy_image(data->mlx_ptr, data->tex.ea);
	if (data->tex.we)
		mlx_destroy_image(data->mlx_ptr, data->tex.we);
	if (data->tex.so)
		mlx_destroy_image(data->mlx_ptr, data->tex.so);
	if (data->tex.no)
		mlx_destroy_image(data->mlx_ptr, data->tex.no);
	if (data->tex.fl)
		mlx_destroy_image(data->mlx_ptr, data->tex.fl);
	if (data->tex.ce)
		mlx_destroy_image(data->mlx_ptr, data->tex.ce);
	if (n)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	mlx_destroy_display(data->mlx_ptr);
	while (++i < 4)
		if (data->txtr[i])
			free(data->txtr[i]);
}

int	graphical(t_data *data)
{
	init_data(data);
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, W_WIDTH, W_HEIGHT, "Cub3D");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (1);
	}
	if (init_texture(data, CUBE_SIDE))
	{
		destroy_all(data, 1, -1);
		free(data->mlx_ptr);
		return (1);
	}
	data->rendu = mlx_new_image(data->mlx_ptr, W_WIDTH, W_HEIGHT);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &button_pressed, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &button_released, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, ft_close, data);
	mlx_loop(data->mlx_ptr);
	destroy_all(data, 0, -1);
	free(data->mlx_ptr);
	return (0);
}
