/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g6_game2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:04:12 by iderighe          #+#    #+#             */
/*   Updated: 2022/08/31 14:04:14 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	find(float x, float y, t_img *tex)
{
	x = x * tex->width;
	y = y * tex->height;
	return (((int *)tex->data)[(int)y * tex->width + (int)x]);
}
