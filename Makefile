# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 13:31:18 by scaussin          #+#    #+#              #
#    Updated: 2016/03/19 17:02:07 by scaussin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 =			server

NAME2 =			client

CC =			gcc $(FLAGS) $(INCLUDES)

LIBFT =			-L./libft -lft

LIB =			./libft/libft.a

INCLUDES =		-I./includes -I./libft/includes

SRC1 =			src_server/check_fd.c \
				src_server/clean_fd.c \
				src_server/client_read.c \
				src_server/client_write.c \
				src_server/do_select.c \
				src_server/init_fd.c \
				src_server/main.c \
				src_server/srv_accept.c \
				src_server/x.c



SRC2 =			src_client/main.c

OBJ1 =			$(SRC1:.c=.o)

OBJ2 =			$(SRC2:.c=.o)

FLAGS =			-Wall -Wextra -Werror

all:			$(NAME1) $(NAME2)

$(LIB):
				@echo "\033[32m[Make]\t\t\033[0m[Make] libft\t\t" | tr -d '\n'
				Make -C libft
				@echo "\033[32mOK\033[0m"

$(NAME1):		$(LIB) $(OBJ1)
				@echo "\t\t[Make] $(NAME1)\t\t" | tr -d '\n'
				$(CC) -o $(NAME1) $(OBJ1) $(LIBFT)
				@echo "\033[32mOK\033[0m"

$(NAME2):		$(LIB) $(OBJ2)
				@echo "\t\t[Make] $(NAME2)\t\t" | tr -d '\n'
				$(CC) -o $(NAME2) $(OBJ2) $(LIBFT)
				@echo "\033[32mOK\033[0m"

clean:
				@echo "\033[31m[clean]\t\t\033[0m[clean] libft\t\t" | tr -d '\n'
				Make -C libft clean
				@echo "\033[32mOK\033[0m"
				@echo "\t\t[clean] .o files\t" | tr -d '\n'
				rm -f $(OBJ1) $(OBJ2)
				@echo "\033[32mOK\033[0m"

fclean:
				@echo "\033[31m[fclean]\t\033[0m[fclean] libft\t\t" | tr -d '\n'
				Make -C libft fclean
				@echo "\033[32mOK\033[0m"
				@echo "\t\t[clean] .o files\t\033[32mOK\033[0m"
				@echo "\t\trm $(NAME1) $(NAME2)\t" | tr -d '\n'
				rm -f $(OBJ1) $(OBJ2) $(NAME1) $(NAME2)
				@echo "\033[32mOK\033[0m"

re:				fclean all

.PHONY:			all clean re fclean
.SILENT:

%.o:			%.c
				$(CC) -c $< -o $@