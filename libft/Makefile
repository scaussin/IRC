#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/23 16:45:48 by scaussin          #+#    #+#              #
#    Updated: 2015/01/20 17:18:31 by scaussin         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRC =	ft_atoi.c ft_bzero.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
		ft_memset.c ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c \
		ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c \
		ft_strnstr.c ft_strstr.c ft_tolower.c ft_toupper.c ft_isprint.c \
		ft_isalnum.c ft_strrchr.c ft_memalloc.c ft_memdel.c ft_strnew.c \
		ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
		ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c \
		ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c \
		ft_putendl.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
		ft_lstiter.c ft_lstmap.c get_next_line.c ft_swap_int.c \
		ft_getnbr.c ft_strsplit_nbr.c ft_strdup2d.c ft_printf.c \
		ft_ptr_fnct_2.c ft_ptr_fnct.c ft_putnbr_2.c ft_putnbr_sc.c \
		ft_utility_2.c ft_utility.c ft_strlen_2d.c

CC =	@gcc $(FLAGS) -I includes

OBJ =	$(SRC:.c=.o)

FLAGS =	-Wall -Werror -Wextra

RM =	rm -rf

all:		$(NAME)

$(NAME):	includes/libft.h $(OBJ)
	$(CC) -c $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	$(RM) $(OBJ)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.phony: all $(NAME) clean fclean re
