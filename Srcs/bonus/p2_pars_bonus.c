/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p2_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoinus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:04:37 by acoinus           #+#    #+#             */
/*   Updated: 2022/09/01 17:47:09 by acoinus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	valid_tex_path(t_data *data, char *s, int i)
{
	int	fd;

	data->txtr[i] = ft_strdup(s);
	if (data->txtr[i] == NULL)
		return (1);
	else
	{
		data->tx[i] = 1;
		fd = open(data->txtr[i], O_RDONLY);
		if (fd == -1)
		{
			data->tex_switch++;
			return (1);
		}
		close(fd);
	}
	return (0);
}

int	set_texture(char *s, char c, t_data *data)
{
	if (c == 'N')
		if (valid_tex_path(data, s, 0))
			return (1);
	if (c == 'S')
		if (valid_tex_path(data, s, 1))
			return (1);
	if (c == 'E')
		if (valid_tex_path(data, s, 2))
			return (1);
	if (c == 'W')
		if (valid_tex_path(data, s, 3))
			return (1);
	return (0);
}

static int	check_open(char *s_cub, t_data *data)
{
	data->fd = 0;
	data->fd = open(s_cub, O_DIRECTORY);
	if (data->fd > 0)
		return (ft_error(2, data->fd));
	data->fd = open(s_cub, O_RDONLY);
	if (data->fd < 0)
		return (ft_error(3, data->fd));
	if (data->fd > 0)
	{
		if (elmt_checker(0, NULL, data, 0))
		{
			data->tex_switch++;
			return (1);
		}
	}
	close(data->fd);
	return (0);
}

int	check_cub(char *s, char *cub, int cub_len)
{
	int	s_len;

	if (!s)
		return (1);
	s_len = ft_strlen(s);
	while (cub_len >= 0)
	{
		if (s[s_len] == cub[cub_len])
		{
			s_len--;
			cub_len--;
		}
		else
			break ;
	}
	if (cub_len == -1 && (s[s_len] && s[s_len] != '.' && s[s_len] != '/'))
		return (0);
	return (1);
}

int	pars(t_data *data)
{
	if (check_cub(data->s_cub, ".cub", 4))
		return (ft_error(1, -1));
	if (check_open(data->s_cub, data))
		return (1);
	return (0);
}
