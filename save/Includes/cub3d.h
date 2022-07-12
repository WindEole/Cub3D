/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iderighe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:12:58 by iderighe          #+#    #+#             */
/*   Updated: 2021/12/13 11:00:08 by iderighe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <string.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define TRUE 1
# define FALSE 0
# define PI 64
//# define BUFFER_SIZE 8

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define GREY "\033[1;37m"
# define RESET "\033[0m"

typedef struct s_dll t_dll;

typedef struct s_adm
{
	t_dll	*head;
	t_dll	*tail;
	t_dll	*play;
	void	*p[7];
	int		y;
	int		e;
	int		op;
	int		te;
	int		col;
	int		color; // ajout cub
	char	addr; // ajour cub
}	t_adm;

struct s_dll
{
	char	c;
	int		x;
	int		y;
	t_dll	*r;
	t_dll	*l;
};

typedef struct s_plp
{
	int	px;
	int	py;
	int	tx;
	int	ty;
}	t_plp;

// create_lst_map.c

t_adm	**ft_create_map(t_adm **adm, int fd, int y);
int		ft_count_nb(t_adm *adm);

// graphical.c

int		ft_graphical(t_adm **adm, int x, int y);

// movement.c

int		ft_close(t_adm **adm);
int		ft_vert(t_adm **adm, void **p, int i);
int		ft_hori(t_adm **adm, void **p, int i);

// error_free.c

int		ft_error(char *s, int ret);
void	*ft_free_line(char *s, int ret, void *r);
void	*ft_free_allist(t_adm **adm, int y, void *r);
t_adm	*ft_free_adm_u(t_adm *adm);

// all_display.c

void	all_display(t_adm **adm, int y);
#endif
