##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## A simple Makefile to compile my lib network
##

NAME	=	libmy_network.a

SRC	=	src/create_socket.c	\
		src/tcp_message/tcp_new_message.c	\
		src/tcp_message/tcp_add_to_message.c	\
		src/tcp_message/tcp_get_message.c	\
		src/tcp_message/tcp_is_waiting_message.c	\
		src/tcp_message/tcp_send_message.c	\
		src/tcp_message/tcp_receive_message.c	\

CFLAGS = 	-Iinclude -W -Wall -Wshadow -Wextra -Werror

OBJ	=	$(SRC:.c=.o)

all:	$(OBJ)
	ar rc $(NAME) $(OBJ)
	mv $(NAME) ./../

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ./../$(NAME)

re: fclean all

.PHONY: all clean fclean re
