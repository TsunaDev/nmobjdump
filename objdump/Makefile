##
## EPITECH PROJECT, 2018
## nmobjdump
## File description:
## Makefile to compile objdump
##

SRC	=	src/objdump64.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-D_GNU_SOURCE

NAME	=	my_objdump

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
