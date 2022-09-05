/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g3_movekey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:06:17 by iderighe          #+#    #+#             */
/*   Updated: 2022/08/18 18:06:21 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	turn_right(t_data *data)
{
	data->play.pa += 0.1 * SPEED;
	if (data->play.pa > 2 * M_PI)
		data->play.pa -= 2 * M_PI;
	data->play.pdx = cos(data->play.pa) * SPEED * 5;
	data->play.pdy = sin(data->play.pa) * SPEED * 5;
}

void	turn_left(t_data *data)
{
	data->play.pa -= 0.1 * SPEED;
	if (data->play.pa < 0)
		data->play.pa += 2 * M_PI;
	data->play.pdx = cos(data->play.pa) * SPEED * 5;
	data->play.pdy = sin(data->play.pa) * SPEED * 5;
}

void	deal_key(t_data *data)
{
	if (data->key.s == 1)
		move_backward(data);
	if (data->key.w == 1)
		move_forward(data);
	if (data->key.a == 1)
		move_left(data);
	if (data->key.d == 1)
		move_right(data);
	if (data->key.l == 1)
		turn_left(data);
	if (data->key.r == 1)
		turn_right(data);
}

int	button_released(int key, t_data *data)
{
	if ((key == 115 || key == 65364))
		data->key.s = 0;
	if ((key == 119 || key == 65362))
		data->key.w = 0;
	if (key == 97)
		data->key.a = 0;
	if (key == 100)
		data->key.d = 0;
	if (key == 65361)
		data->key.l = 0;
	if (key == 65363)
		data->key.r = 0;
	return (0);
}

int	button_pressed(int key, t_data *data)
{
	if ((key == 115 || key == 65364))
		data->key.s = 1;
	if ((key == 119 || key == 65362))
		data->key.w = 1;
	if (key == 97)
		data->key.a = 1;
	if (key == 100)
		data->key.d = 1;
	if (key == 65361)
		data->key.l = 1;
	if (key == 65363)
		data->key.r = 1;
	if (key == 65307)
		ft_close(data);
	return (0);
}
