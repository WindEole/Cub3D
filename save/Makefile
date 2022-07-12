# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iderighe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 17:24:14 by iderighe          #+#    #+#              #
#    Updated: 2021/12/10 11:23:22 by iderighe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

INC		=	Includes

CC		=	clang
FLAGS	=	-Wall -Wextra -Werror -I $(INC)
CDEP	=	-MMD
CFA		=	-fsanitize=address -g3
RM		=	/usr/bin/rm -rf

LIB		=	-L./Libft -lft -L./minilibx-linux -lmlx -lXext -lX11

vpath %.c Srcs

SRC		=	Srcs/main_parse.c \
			Srcs/create_lst_map.c \
			Srcs/graphical.c \
			Srcs/movement.c \
			Srcs/error_free.c \
			Srcs/all_display.c \

OBJ		=	$(SRC:Srcs/%.c=Objs/%.o)
DEP		=	$(SRC:Srcs/%.c=Objs/%.d)


all			:	obj libft $(NAME)

-include $(DEP)

$(NAME)		:	$(OBJ)
				$(MAKE) -C minilibx-linux
				$(CC) $(FLAGS) -o $(NAME) $(SRC) $(LIB)

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
