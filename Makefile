# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sboeuf <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/16 19:40:15 by sboeuf            #+#    #+#              #
#    Updated: 2014/02/16 19:40:18 by sboeuf           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= gcc

NAME		= rtv1

INCLUDE		= ./includes/

SRCS		=	main.c				\
				rtv1.c				\
				camera.c			\
				d_vect.c			\
				ray.c				\
				f_ray.c				\
				vect.c				\
				color.c				\
				f_color.c			\
				f_color_2.c			\
				light.c				\
				plane.c				\
				sphere.c			\
				v_vect.c			\
				scene.c				\
				ft_get_next_line.c	\
				ft_atodouble.c		\
				f_sphere.c			\
				f_plane.c			\
				f_light.c			\
				window.c			\
				img_fct.c			\
				draw.c				\
				hook_fct.c			\
				cylinder.c			\
				f_cylinder.c		\
				intersection.c		\

OBJS		= $(SRCS:.c=.o)

CFLAGS		= -Wall -Werror -Wextra -g

CLFLAGS     += -L/usr/X11/lib -lmlx -lXext -lX11 -lm
CLFLAGS     += -L includes/libft -lft
LDFLAGS 	= -I $(DIR_LIBFT)/includes

DIR_LIBFT	= ./includes/libft

all:		$(NAME)

%.o:		%.c
			$(CC) $(CFLAGS) -c $^ -I $(INCLUDE) -L -lft

$(NAME):	$(DIR_LIBFT)/libft.a $(OBJS)
			$(CC) -o $(NAME) $(OBJS) $(CLFLAGS) $(CFLAGS) $(LDFLAGS)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

$(DIR_LIBFT)/libft.a:
	make  -f Makefile -C $(DIR_LIBFT)

re:			fclean all

.PHONY:		all clean re fclean
