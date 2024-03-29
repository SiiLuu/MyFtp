##
## EPITECH PROJECT, 2020
## NWP_myftp_2019
## File description:
## Makefile
##

SRC		=	src/main.c 				\
			src/error.c				\
			src/server.c			\
			src/read_client.c		\
			src/exec_commands.c 	\
			src/cwd.c	 			\
			src/dele.c 				\
			src/commands.c 			\
			src/list.c				\
			src/passive_mode.c 		\
			src/active_mode.c 		\
			src/downloading.c 		\
			src/upload.c 			\

OBJ		=	$(SRC:.c=.o)

NAME	=	myftp

CFLAGS 	=	-W -Wall -Wextra -I./include

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re:	fclean all

.PHONY: clean fclean re
