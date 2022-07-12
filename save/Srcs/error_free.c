/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 14:32:43 by iderighe          #+#    #+#             */
/*   Updated: 2021/12/05 00:05:45 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(char *s, int r)
{
	printf(RED"\n");
	ft_putstr_fd(s, 2);
	printf(RESET"\n");
	return (r);
}

t_adm	*ft_free_adm_u(t_adm *adm)
{
	t_dll	*now;

	if (!adm)
		return (NULL);
	now = adm->head;
	while (now->r != NULL)
	{
		now = now->r;
		free(now->l);
	}
	free(now);
	free(adm);
	return (NULL);
}

void	*ft_free_allist(t_adm **adm, int y, void *r)
{
	int	i;

	i = -1;
	if (!adm)
		return (r);
	while (++i < y)
		ft_free_adm_u(adm[i]);
	free(adm);
	return (r);
}

void	*ft_free_line(char *s, int ret, void *r)
{
	if (ret == -1)
		return (r);
	if (!s)
		return (r);
	free(s);
	return (r);
}
