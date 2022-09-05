/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p7_strjoin_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoinus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 17:21:23 by acoinus           #+#    #+#             */
/*   Updated: 2022/08/29 16:03:55 by acoinus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/cub3d.h"

int	ft_strjoin_map_suite(int *j, t_data *data, int *str, int n)
{
	int	i;

	while (j[0] < data->map.x)
	{
		str[++j[1]] = 32;
		j[0]++;
	}
	i = -1;
	data->mapext = malloc(sizeof(int) * (n * data->map.x));
	if (data->mapext == NULL)
		return (free(str), 1);
	while (++i < n * data->map.x)
		data->mapext[i] = str[i];
	free(str);
	str = NULL;
	return (0);
}

int	ft_strjoin_map(t_data *data, char *s2, int i, int n)
{
	int		j[2];
	int		*str;

	j[1] = -1;
	j[0] = -1;
	str = malloc(sizeof(int) * (n * data->map.x));
	if (str == NULL)
		return (1);
	while (data->mapext && i < (n - 1) * data->map.x)
		str[++j[1]] = data->mapext[i++];
	if (data->mapext)
	{
		free(data->mapext);
		data->mapext = NULL;
	}
	while (s2 && s2[++j[0]])
	{
		if ((int)s2[j[0]] >= 48 && (int)s2[j[0]] < 58)
			str[++j[1]] = (int)s2[j[0]] - 48;
		else
			str[++j[1]] = (int)s2[j[0]];
	}
	return (ft_strjoin_map_suite(j, data, str, n));
}
