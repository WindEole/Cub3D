/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 22:00:07 by iderighe          #+#    #+#             */
/*   Updated: 2021/12/08 16:07:04 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	all_display(t_adm **adm, int y)
{
	t_dll	*now;
	int		i;
	int		s;

	s = y;
	i = -1;
	printf(YELLOW"\ny = [%d]\n"RESET"\n", y);
	printf(YELLOW"\na[y] = [%d]\n"RESET"\n", adm[0]->y);
	while (++i < y)
	{
		now = adm[i]->head;
		printf(RED"NULL -> ");
		while (now != NULL)
		{
			printf(GREEN"%c", now->c);
			now = now->r;
		}
		printf(RED" -> NULL"RESET"\n");
	}

	y = s;
	i = -1;
	printf(YELLOW"\nVerif des [x]\n"RESET"\n");
	while (++i < y)
	{
		now = adm[i]->head;
		printf(RED"NULL -> |");
		while (now != NULL)
		{
			printf(GREEN"%d|", now->x);
			now = now->r;
		}
		printf(RED" -> NULL"RESET"\n");
	}

	y = s;
	i = -1;
	printf(YELLOW"\nVerif des [y]\n"RESET"\n");
	while (++i < y)
	{
		now = adm[i]->head;
		printf(RED"NULL -> |");
		while (now != NULL)
		{
			printf(GREEN"%d|", now->y);
			now = now->r;
		}
		printf(RED" -> NULL"RESET"\n");
	}
}*/
