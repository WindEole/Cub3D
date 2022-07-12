/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:12:18 by iderighe          #+#    #+#             */
/*   Updated: 2021/12/08 15:28:03 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//
float px, py; //player position
//

static int	ft_count_elm(t_adm **adm, t_dll *now, int y, int *v)
{
	v[1] = 0;
	v[2] = 0;
	v[3] = 0;
	v[0] = -1;
	while (++v[0] < y)
	{
		now = adm[v[0]]->head;
		while (now != NULL)
		{
			if ((now->c == 'N' || now->c == 'S' || now->c == 'E' || now->c == 'W') && v[1]++ != -1)
				adm[0]->play = now;
			// else if (now->c == 'E')
			// 	v[2]++;
			// else if (now->c == 'C')
			// 	v[3]++;
			else if (now->c != '1' && now->c != '0')
				return (FALSE);
			now = now->r;
		}
	}
	adm[0]->col = v[3];
	if (v[1] != 1 || v[2] <= 0 || v[3] <= 0)
		return (FALSE);
	return (TRUE);
}

static int	ft_valid_char(t_adm **adm, int y)
{
	t_dll	*now;
	int		t;
	int		v[4];

	t = -1;
	while (++t < y)
	{
		now = adm[t]->head;
		if (t == 0 || t == y - 1)
		{
			while (now != NULL)
			{
				if (now->c != '1')
					return (FALSE);
				now = now->r;
			}
		}
		else if (adm[t]->head->c != '1' || adm[t]->tail->c != '1')
			return (FALSE);
	}
	if (!ft_count_elm(adm, now, y, v))
		return (FALSE);
	return (TRUE);
}

static int	ft_count_rows(int fd, int y, int v)
{
	char	*line;
	int		ret;
	int		len;

	ret = get_next_line(fd, &line);
	if (ret == -1)
		return (ft_error("Error\n- does the file exist ?", -1));
	len = ft_strlen(line);
	free(line);
	y++;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (-1);
		if ((line[0] != '\0' && ft_strlen(line) != len)
			|| (line[0] == '\0' && ret == 1))
			v++;
		if (line[0] != '\0')
			y++;
		free(line);
	}
	if (v)
		return (-1);
	return (y);
}

static int	ft_valid_file(int ac, char *s)
{
	int	i;
	int	fd;

	if (ac < 2)
		return (ft_error("Error\n- no argument", 0));
	if (ac > 2)
		return (ft_error("Error\n- too much arguments", 0));
//		printf(GREEN"Only the first file will be used !"RESET"\n");
	fd = open(s, O_RDONLY);
	if (fd < 0)
		return (ft_error("Error\n- file doesn't exist", 0));
	close(fd);
	if (open(s, O_DIRECTORY) > 0)
		return (ft_error("Error\n- arg is a directory", 0));
	i = ft_strlen(s) - 1;
	if (ft_strlen(s) >= 5)
	{
		if (s[i] == 'b' && s[--i] == 'u' && s[--i] == 'c' && s[--i] == '.')
			return (TRUE);
		else
			return (ft_error("Error\n- arg is not a [.cub] file", 0));
	}
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_adm	**adm;
	int		y[2];

	if (!ft_valid_file(ac, av[1]))
		return (EXIT_FAILURE);
	y[1] = open(av[1], O_RDONLY);
	y[0] = ft_count_rows(y[1], 0, 0);
	close(y[1]);
	if (y[0] == -1)
		return (ft_error("Error\n- invalid map : not rectangular", 1));
	adm = malloc(sizeof(*adm) * y[0]);
	y[1] = open(av[1], O_RDONLY);
	adm = ft_create_map(adm, y[1], 0);
	close(y[1]);
	if (adm == NULL)
		return (EXIT_FAILURE);
	adm[0]->y = y[0];
	if (!ft_valid_char(adm, y[0]))
	{
		ft_free_allist(adm, y[0], NULL);
		return (ft_error("Error\n- invalid map : misconfiguration", 1));
	}
	ft_graphical(adm, ft_count_nb(adm[0]), y[0]);
	ft_free_allist(adm, y[0], NULL);
	return (EXIT_SUCCESS);
}
