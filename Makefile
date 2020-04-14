##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## A simple Makefiled
##

NAME	= myftp

SRC	=	src/myftp.c	\
		src/get_user_info.c	\
		src/exit_properly.c	\
		src/utils/my_strtok.c	\
		src/utils/get_size_array.c	\
		src/utils/free_array.c	\
		src/fd/close_fd.c	\
		src/fd/set_fd_set.c	\
		src/fd/socket_error.c	\
		src/server/init_server_info.c	\
		src/server/start_server.c	\
		src/server/stop_server.c	\
		src/server/running_server.c	\
		src/server/quit_client.c	\
		src/server/manage_timeout_select.c	\
		src/server/handle_socket_activities.c	\
		src/server/handle_client_activities.c	\
		src/server/data_process/add_process_to_client.c	\
		src/server/data_process/wait_data_process.c	\
		src/client/client_error.c	\
		src/client/delete_client.c	\
		src/client/new_client.c	\
		src/client/is_new_client.c	\
		src/client/is_client_login.c	\
		src/client/add_message.c	\
		src/commands/quit.c	\
		src/commands/user.c	\
		src/commands/pass.c	\
		src/commands/noop.c	\
		src/commands/help.c	\
		src/commands/pwd.c	\
		src/commands/dele.c	\
		src/commands/cwd.c	\
		src/commands/cdup.c	\
		src/commands/pasv.c	\
		src/commands/port.c	\
		src/commands/list.c	\
		src/commands/retr.c	\
		src/commands/stor.c	\
		src/commands/handle_mode.c	\

SRC_MAIN	=	src/main.c	\

NAME_TESTS	=	unit_test

SRC_TESTS =		$(SRC)	\
				tests/tests_redirect.c	\

CFLAGS += 	-W -Wall -Wextra -Wshadow -Werror -Iinclude \
			-I./lib/my_network/include -I./lib/my_list/include

LDFLAGS += -lmy_list -lmy_network -L./lib

LDFLAGS_TESTS = -lcriterion --coverage	-lmy_list -lmy_network -L./lib\

OBJ	=	$(SRC:.c=.o) $(SRC_MAIN:.c=.o)

OBJ_TESTS =	$(SRC_TESTS:.c=.o)

CC	=	gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./lib/my_network
	$(MAKE) -C ./lib/my_list
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	$(MAKE) -C ./lib/my_network clean
	$(MAKE) -C ./lib/my_list clean
	rm -rf $(OBJ)
	rm -rf $(OBJ_TESTS)

fclean: clean
	$(MAKE) -C ./lib/my_network fclean
	$(MAKE) -C ./lib/my_list fclean
	rm -rf $(NAME)

rclean:
	rm -rf $(NAME_TESTS)
	find . -type f -name "*.gcno" -delete -or -name "*.gcda" -delete

tests_run: LDFLAGS += -lgcov --coverage
tests_run: CFLAGS += -fprofile-arcs -ftest-coverage
tests_run: re
	#./tests/test_ftp.sh 127.0.0.1 3100

coverage:
	sudo gcovr -e tests/

debug : CFLAGS += -g
debug : re

re: fclean all

.PHONY: all clean fclean re tests_run rclean
