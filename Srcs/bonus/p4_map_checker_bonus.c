/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p4_map_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoinus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:07:21 by acoinus           #+#    #+#             */
/*   Updated: 2022/09/03 14:57:54 by acoinus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

static int	map_storing(char *line, t_data *data, int x)
{
	int	n;

	close(data->fd);
	data->fd = open(data->s_cub, O_RDONLY);
	get_next_line(data->fd, &line, 0, 1);
	while (--x > 0)
	{
		free(line);
		get_next_line(data->fd, &line, 0, 1);
	}
	free(line);
	line = NULL;
	n = 1;
	while (get_next_line(data->fd, &line, 0, 1))
	{
		ft_strjoin_map(data, line, 0, n);
		n++;
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	if (!data->mapext)
		return (ft_error(5, data->fd));
	return (p_checker(data, -1));
}

int	map_checker(char *line, t_data *data, int x)
{
	int	n;

	n = 1;
	data->map.y = 0;
	data->map.x = ft_strlen(line);
	while (line)
	{
		if (line[0] == '\0' && !n)
			return (free(line), map_storing(NULL, data, x - 1));
		else if (line[0] == '\0' && n)
			return (free(line), ft_error(5, data->fd));
		++data->map.y;
		if (ft_strlen(line) > data->map.x)
			data->map.x = ft_strlen(line);
		free(line);
		line = NULL;
		n = get_next_line(data->fd, &line, 0, 1);
	}
	return (0);
}
