# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 13:31:18 by scaussin          #+#    #+#              #
#    Updated: 2016/09/28 16:40:33 by scaussin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 =			serveur

NAME2 =			client

CC =			gcc $(FLAGS) $(INCLUDES)

LIBFT =			-L./libft -lft

LIB =			./libft/libft.a

INCLUDES =		-I./includes -I./libft/includes

SRC1 =			src_server/clean_fd.c \
				src_server/client_read.c \
				src_server/client_write.c \
				src_server/cmd.c \
				src_server/cmd_2.c \
				src_server/cmd_join.c \
				src_server/cmd_list.c \
				src_server/cmd_nick.c \
				src_server/cmd_privmsg.c \
				src_server/cmd_who.c \
				src_server/lexer.c \
				src_server/main.c \
				src_server/parser.c \
				src_server/protocol.c \
				src_server/select.c \
				src_server/srv_accept.c \
				src_server/tools.c \
				src_server/x.c

SRC2 =			src_client/buf.c \
				src_client/connect.c \
				src_client/lexer_client.c \
				src_client/lexer_server_1.c \
				src_client/lexer_server_2.c \
				src_client/main.c \
				src_client/parsing_client_1.c \
				src_client/parsing_client_2.c \
				src_client/parsing_client_3.c \
				src_client/parsing_server_1.c \
				src_client/parsing_server_2.c \
				src_client/parsing_server_3.c \
				src_client/protocol_1.c \
				src_client/protocol_2.c \
				src_client/read.c \
				src_client/select.c \
				src_client/tools_1.c \
				src_client/tools_2.c \
				src_client/write.c

OBJ1 =			$(SRC1:.c=.o)

OBJ2 =			$(SRC2:.c=.o)

FLAGS =			-Wall -Wextra -Werror -g

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
