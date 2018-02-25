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
	mv nm/$(NM) ./

$(OBJDUMP):
	make -C objdump/
	mv objdump/$(OBJDUMP) ./

clean:
	make clean -C objdump/
	make clean -C nm/

fclean:	clean
	rm -f $(NM)
	rm -f $(OBJDUMP)

re:	fclean all

.PHONY:	all compile clean fclean re
