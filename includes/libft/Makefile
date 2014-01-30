# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/20 16:27:35 by mchoong           #+#    #+#              #
#    Updated: 2014/01/11 18:00:33 by lfouquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
GCCW = gcc -Wall -Wextra -Werror
SRC = ft_isascii.c ft_memcmp.c ft_strchr.c ft_strlen.c ft_strrchr.c 		\
		ft_atoi.c ft_isdigit.c ft_memcpy.c ft_strcmp.c ft_strncat.c 		\
		ft_strstr.c ft_bzero.c ft_isprint.c ft_memmove.c ft_strcpy.c 		\
		ft_strncmp.c ft_tolower.c ft_isalnum.c ft_memccpy.c ft_memset.c 	\
		ft_strdup.c ft_strncpy.c ft_toupper.c ft_isalpha.c ft_memchr.c 		\
		ft_strcat.c ft_strlcat.c ft_strnstr.c 								\
		ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c 		\
		ft_striter.c ft_striteri.c ft_strmap.c ft_putchar.c ft_putstr.c 	\
		ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c 		\
		ft_strtrim.c ft_putnbr.c ft_strsplit.c ft_itoa.c ft_putendl.c 		\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c 		\
		ft_lstnew.c ft_lstdelone.c ft_lstadd.c ft_lstiter.c ft_lstmap.c 	\
		ft_lstdel.c 														\
		ft_putmem.c ft_putnbr_base.c ft_atoi_base.c ft_lstadd_tail.c

OBJECT = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	$(GCCW) -I./includes -c $(SRC)
	ar rc $(NAME) $(OBJECT)
	ranlib $(NAME)

clean:
	/bin/rm -f $(OBJECT)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
