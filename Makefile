##
## EPITECH PROJECT, 2018
## nmobjdump
## File description:
## Makefile to compile objdump
##

NM	=	my_nm

OBJDUMP	=	my_objdump

all:	$(NM) $(OBJDUMP)

nm:		$(NM)

objdump:	$(OBJDUMP)

$(NM):
	make -C nm/
	mv nm/my_nm ./

$(OBJDUMP):
	make -C objdump/
	mv objdump/my_objdump ./

clean:
	make clean -C objdump/

fclean:
	make clean -C objdump/
	rm -f my_objdump
	rm -f my_nm

re:	fclean all

.PHONY:	all compile clean fclean re
