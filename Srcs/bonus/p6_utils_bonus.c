/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p6_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoinus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:27:02 by acoinus           #+#    #+#             */
/*   Updated: 2022/09/03 15:15:58 by acoinus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

char	*ft_strdup_n(const char *s, int n)
{
	char	*d;
	size_t	i;

	d = (char *)malloc(sizeof(char) * n + 1);
	if (d == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (s[i] && (int)i < n)
		{
			d[i] = s[i];
			i++;
		}
		d[i] = '\0';
		return (d);
	}
}

int	ft_strlen_i(int *str)
{
	int	i;

	i = 0;
	while ((char)str[i])
		i++;
	return (i);
}

int	ft_isdigit_cub(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == ',')
			continue ;
		if (s[i] < 48 || s[i] > 57)
			return (1);
	}
	return (0);
}

int	ft_error(int err, int fd)
{
	char	*line;

	if (err == 0)
		ft_putstr_fd("Error\n./Wrong argument number\n", 2);
	else if (err == 1)
		ft_putstr_fd("Error\n./Wrong file path or extension [file.cub]\n", 2);
	else if (err == 2)
		ft_putstr_fd("Error\n./File required instead of a directory\n", 2);
	else if (err == 3)
		ft_putstr_fd("Error\n./Error while opening the file\n", 2);
	else if (err == 4)
		ft_putstr_fd("Error\n./Error with map elements\n", 2);
	else if (err == 5)
		ft_putstr_fd("Error\n./Error in map making\n", 2);
	if (err == 4 || err == 5)
	{
		get_next_line(fd, &line, 1, 1);
		free(line);
	}
	if (err > 1)
		close(fd);
	return (1);
}
