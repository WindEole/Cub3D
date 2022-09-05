/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoinus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:57:06 by acoinus           #+#    #+#             */
/*   Updated: 2022/09/03 15:16:19 by acoinus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_n(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_strcut(char *str)
{
	char	*cut_to_n;
	int		i;

	cut_to_n = malloc(sizeof(char) * (ft_strn(str) + 1));
	if (cut_to_n == NULL)
		return (NULL);
	i = 0;
	if (str)
	{
		while (str[i] && str[i] != '\n')
		{
			cut_to_n[i] = str[i];
			i++;
		}
	}
	cut_to_n[i] = '\0';
	return (cut_to_n);
}

static char	*ft_saver(char *str, int x)
{
	int	i;
	int	j;

	if (!str)
		return (NULL);
	i = ft_strn(str);
	if (x || !str[i])
	{
		free(str);
		return (NULL);
	}
	if (str && str[i])
		i++;
	j = 0;
	while (str && str[i])
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

static void	gnl_suite(char **line, char **str, int x)
{
	*line = ft_strcut(*str);
	*str = ft_saver(*str, x);
	return ;
}

int	get_next_line(int fd, char **line, int x, int r)
{
	static char	*str;
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	if (ft_check_n(str) == 0)
		r = read(fd, buf, BUFFER_SIZE);
	while (ft_check_n(str) == 0 && r != 0)
	{
		if (r == -1)
			return (-1);
		buf[r] = '\0';
		tmp = str;
		str = ft_strjoin_gnl(tmp, buf);
		free(tmp);
		if (ft_check_n(str) == 0)
			r = read(fd, buf, BUFFER_SIZE);
	}
	gnl_suite(line, &str, x);
	if (r == 0)
		return (0);
	return (1);
}
