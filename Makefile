# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iderighe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 17:24:14 by iderighe          #+#    #+#              #
#    Updated: 2022/09/01 17:52:25 by acoinus          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#******************************************************************************#
#                               MAKEFILE CUB                                   #
#******************************************************************************#

NAME	=	cub3D

INC		=	Includes

CC		=	clang
FLAGS	=	-Wall -Wextra -Werror -g -I$(INC)
CDEP	=	-MMD
CFA		=	-fsanitize=address
# si on veut voir les perf d'opti : flag -O3 (c'est un o majuscule) ATTENTION : interdit pour passer le projet !!
RM		=	/usr/bin/rm -rf

LIB		=	-L./Libft -lft -L./minilibx-linux -lmlx -lXext -lX11 -lm

vpath %.c Srcs

SRC		=	Srcs/p1_main.c \
			Srcs/p2_pars.c \
			Srcs/p3_elmt_checker.c \
			Srcs/p4_map_checker.c \
			Srcs/p5_wall_checker.c \
			Srcs/p6_utils.c \
			Srcs/p7_strjoin_map.c \
			Srcs/g1_graphical.c \
			Srcs/g2_init.c \
			Srcs/g3_movekey.c \
			Srcs/g4_movement.c \
			Srcs/g5_raycasting1.c \
			Srcs/g5_raycasting2.c \
			Srcs/g6_game1.c \
			Srcs/g6_game2.c \

OBJ		=	$(SRC:Srcs/%.c=Objs/%.o)
DEP		=	$(SRC:Srcs/%.c=Objs/%.d)


all			:	obj libft $(NAME)

-include $(DEP)

$(NAME)		:	$(OBJ)
				$(MAKE) -C minilibx-linux
				$(CC) -o $(NAME) $(SRC) $(LIB)

obj			:
				@if [ ! -d "./Objs" ]; then\
					echo "mkdir -p Objs";\
					mkdir -p Objs;\
				fi
					@echo ""

libft		:
				$(MAKE) -C Libft

Objs/%.o	:	Srcs/%.c
				$(CC) -o $@ -c $< $(FLAGS) $(CDEP)

norm		:
				norminette $(SRC)
				norminette $(INC)
				$(MAKE) -C Libft norm

clean		:
				$(RM) $(OBJ)
				$(RM) Objs

fclean		:	clean
				$(RM) $(NAME)
				$(MAKE) -C Libft fclean
				$(MAKE) -C minilibx-linux clean

fsa			:	fclean obj $(OBJ)
				$(MAKE) -C Libft
				$(MAKE) -C minilibx-linux
				$(CC) $(FLAGS) $(CFA) $(CDEP) -o $(NAME) $(SRC) $(LIB)

fre			:	fclean fsa

re			:	fclean all

.PHONY		:	all obj libft norm clean fclean fsa fre re

#******************************************************************************#
#                               MAKEFILE CUB BONUS                             #
#******************************************************************************#

NAME_B	=	cub3D_bonus

INC_B	=	Includes

CC_B	=	clang
FLAGS	=	-Wall -Wextra -Werror -I$(INC)
CDEP_B	=	-MMD
CFA_B	=	-g3 -fsanitize=address
# si on veut voir les perf d'opti : flag -O3 (c'est un o majuscule) ATTENTION : interdit pour passer le projet !!
RM_B	=	/usr/bin/rm -rf

LIB_B	=	-L./Libft -lft -L./minilibx-linux -lmlx -lXext -lX11 -lm

vpath %.c Srcs/bonus/

SRC_B	=	Srcs/bonus/p1_main_bonus.c \
			Srcs/bonus/p2_pars_bonus.c \
			Srcs/bonus/p3_elmt_checker_bonus.c \
			Srcs/bonus/p4_map_checker_bonus.c \
			Srcs/bonus/p5_wall_checker_bonus.c \
			Srcs/bonus/p6_utils_bonus.c \
			Srcs/bonus/p7_strjoin_map_bonus.c \
			Srcs/bonus/g1_graphical_bonus.c \
			Srcs/bonus/g2_init_bonus.c \
			Srcs/bonus/g3_movekey_bonus.c \
			Srcs/bonus/g4_movement_bonus.c \
			Srcs/bonus/g5_raycasting1_bonus.c \
			Srcs/bonus/g5_raycasting2_bonus.c \
			Srcs/bonus/g6_game1_bonus.c \
			Srcs/bonus/g6_game2_bonus.c \
			Srcs/bonus/g7_minimap_bonus.c \

OBJ_B	=	$(SRC_B:Srcs/bonus/%.c=Objs/%.o)
DEP_B	=	$(SRC_B:Srcs/bonus/%.c=Objs/%.d)


bonus		:	objb libftb $(NAME_B)

-include $(DEP_B)

$(NAME_B)	:	$(OBJ_B)
				$(MAKE) -C minilibx-linux
				$(CC_B) -o $(NAME_B) $(SRC_B) $(LIB_B)

objb		:
				@if [ ! -d "./Objs" ]; then\
					echo "mkdir -p Objs";\
					mkdir -p Objs;\
				fi
					@echo ""

libftb		:
				$(MAKE) -C Libft

Objs/%.o	:	Srcs/bonus/%.c
				$(CC_B) -o $@ -c $< $(FLAGS_B) $(CDEP_B)

normb		:
				norminette $(SRC_B)
				norminette $(INC_B)
				$(MAKE) -C Libft norm

cleanb		:
				$(RM_B) $(OBJ_B)
				$(RM_B) Objs

fcleanb		:	cleanb
				$(RM_B) $(NAME_B)
				$(MAKE) -C Libft fclean
				$(MAKE) -C minilibx-linux clean

fsab		:	fcleanb objb $(OBJ_B)
				$(MAKE) -C Libft
				$(MAKE) -C minilibx-linux
				$(CC_B) $(FLAGS_B) $(CFA_B) $(CDEP_B) -o $(NAME_B) $(SRC_B) $(LIB_B)

freb		:	fcleanb fsab

reb			:	fcleanb bonus

.PHONY		:	bonus objb libftb normb cleanb fcleanb fsab freb reb
