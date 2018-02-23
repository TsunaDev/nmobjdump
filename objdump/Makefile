##
## EPITECH PROJECT, 2018
## nmobjdump
## File description:
## Makefile to compile objdump
##

SRC	=	src/objdump32.c		\
		src/objdump64.c		\
		src/main.c		\
		src/parsing.c		\
		src/errors.c		\
		src/common.c		\
		src/truncated_file.c	\
		src/init_structure.c	\
		src/flags32.c		\
		src/flags64.c		\
		src/strcat_realloc.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-D_GNU_SOURCE -Iinclude -Wall -Wextra -W

NAME	=	my_objdump

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

debug:	CFLAGS += -ggdb3
debug:	re

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
