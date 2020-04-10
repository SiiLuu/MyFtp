##
## EPITECH PROJECT, 2020
## NWP_myftp_2019
## File description:
## Makefile
##

SRC		=	src/main.c 			\
			src/error.c			\
			src/server.c		\

OBJ		=	$(SRC:.c=.o)

NAME	=	myftp

CFLAGS 	=	-W -Wall -Wextra -I./include

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(CFLAGS)
	gcc -o client client.c

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)
	rm -rf client

re:	fclean all

.PHONY: clean fclean re
