/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_lst_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:50:35 by iderighe          #+#    #+#             */
/*   Updated: 2021/12/10 16:12:29 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_count_nb(t_adm *adm)
{
	t_dll	*now;
	int		x;

	now = adm->head;
	if (!now)
		return (FALSE);
	x = 1;
	while (now->r != NULL)
	{
		now = now->r;
		x++;
	}
	return (x);
}

static int	ft_insert(t_adm *adm, char c, int y, int x)
{
	t_dll	*dll;

	dll = malloc(sizeof(*dll));
	if (dll == NULL)
		return (1);
	dll->c = c;
	dll->x = x;
	dll->y = y;
	dll->r = NULL;
	dll->l = adm->tail;
	adm->tail->r = dll;
	adm->tail = dll;
	return (0);
}

static t_adm	*ft_new_list(t_adm *adm, char *s, int y, int x)
{
	t_dll	*dll;

	adm = malloc(sizeof(*adm));
	dll = malloc(sizeof(*dll));
	if (adm == NULL || dll == NULL)
	{
		if (dll != NULL)
			free(dll);
		if (adm != NULL)
			free(adm);
		return (NULL);
	}
	adm->head = dll;
	adm->tail = dll;
	dll->c = s[0];
	dll->x = x;
	dll->y = y;
	dll->r = NULL;
	dll->l = NULL;
	while (s[++x])
		if (ft_insert(adm, s[x], y, x))
			return (ft_free_adm_u(adm));
	return (adm);
}

t_adm	**ft_create_map(t_adm **adm, int fd, int y)
{
	char	*line;
	int		ret;

	ret = get_next_line(fd, &line);
	if (ret == -1)
		return (NULL);
	adm[y] = ft_new_list(adm[y], line, y, 0);
	free(line);
	if (adm[y++] == NULL)
		return (NULL);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			return (ft_free_line(line, ret, NULL));
		if (line[0] == '\0')
			return (ft_free_line(line, ret, adm));
		adm[y] = ft_new_list(adm[y], line, y, 0);
		free(line);
		if (adm[y] == NULL)
			return (ft_free_allist(adm, y + 1, NULL));
		y++;
	}
	close(fd);
	return (adm);
}
