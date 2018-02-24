##
## EPITECH PROJECT, 2018
## nmobjdump
## File description:
## Makefile to compile objdump
##

SRC	=	src/main.c			\
		src/errors.c			\
		src/truncated_file.c		\
		src/init_structure.c		\
		src/init_structure_symtab.c	\
		src/nm64.c			\
		src/flags64.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-D_GNU_SOURCE -Iinclude -Wall -Wextra -W

NAME	=	my_nm

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
