/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g4_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:07:05 by iderighe          #+#    #+#             */
/*   Updated: 2022/08/18 18:07:09 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	check_offset(int p)
{
	int	o;

	if (p < 0)
		o = -10;
	else
		o = 10;
	return (o);
}

void	move_right(t_data *data)
{
	int	index;
	int	next_x;
	int	next_y;
	int	xo;
	int	yo;

	xo = check_offset(data->play.pdx);
	yo = check_offset(data->play.pdy);
	next_x = (data->play.px - data->play.pdy - yo) / CUBE_SIDE;
	next_y = (data->play.py + data->play.pdx + xo) / CUBE_SIDE;
	index = data->play.py / CUBE_SIDE * data->map.x + next_x;
	if (data->mapext[index] == 0 || ft_strchr(data->mapext[index], "NSEW"))
		data->play.px -= data->play.pdy * SPEED;
	index = next_y * data->map.x + data->play.px / CUBE_SIDE;
	if (data->mapext[index] == 0 || ft_strchr(data->mapext[index], "NSEW"))
		data->play.py += data->play.pdx * SPEED;
}

void	move_left(t_data *data)
{
	int	index;
	int	next_x;
	int	next_y;
	int	xo;
	int	yo;

	xo = check_offset(data->play.pdx);
	yo = check_offset(data->play.pdy);
	next_x = (data->play.px + data->play.pdy + yo) / CUBE_SIDE;
	next_y = (data->play.py - data->play.pdx - xo) / CUBE_SIDE;
	index = data->play.py / CUBE_SIDE * data->map.x + next_x;
	if (data->mapext[index] == 0 || ft_strchr(data->mapext[index], "NSEW"))
		data->play.px += data->play.pdy * SPEED;
	index = next_y * data->map.x + data->play.px / CUBE_SIDE;
	if (data->mapext[index] == 0 || ft_strchr(data->mapext[index], "NSEW"))
		data->play.py -= data->play.pdx * SPEED;
}

void	move_forward(t_data *data)
{
	int	index;
	int	next_x;
	int	next_y;
	int	xo;
	int	yo;

	xo = check_offset(data->play.pdx);
	yo = check_offset(data->play.pdy);
	next_x = (data->play.px + data->play.pdx + xo) / CUBE_SIDE;
	next_y = (data->play.py + data->play.pdy + yo) / CUBE_SIDE;
	index = data->play.py / CUBE_SIDE * data->map.x + next_x;
	if (data->mapext[index] == 0 || ft_strchr(data->mapext[index], "NSEW"))
		data->play.px += data->play.pdx * SPEED;
	index = next_y * data->map.x + data->play.px / CUBE_SIDE;
	if (data->mapext[index] == 0 || ft_strchr(data->mapext[index], "NSEW"))
		data->play.py += data->play.pdy * SPEED;
}

void	move_backward(t_data *data)
{
	int	index;
	int	next_x;
	int	next_y;
	int	xo;
	int	yo;

	xo = check_offset(data->play.pdx);
	yo = check_offset(data->play.pdy);
	next_x = (data->play.px - data->play.pdx - xo) / CUBE_SIDE;
	next_y = (data->play.py - data->play.pdy - yo) / CUBE_SIDE;
	index = data->play.py / CUBE_SIDE * data->map.x + next_x;
	if (data->mapext[index] == 0 || ft_strchr(data->mapext[index], "NSEW"))
		data->play.px -= data->play.pdx * SPEED;
	index = next_y * data->map.x + data->play.px / CUBE_SIDE;
	if (data->mapext[index] == 0 || ft_strchr(data->mapext[index], "NSEW"))
		data->play.py -= data->play.pdy * SPEED;
}
