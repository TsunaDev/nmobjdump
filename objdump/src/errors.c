/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Functions that look for error or print them
*/

#include <stdio.h>
#include <elf.h>

int	check_magic_number(unsigned char ident[])
{
	if (ident[EI_MAG0] == ELFMAG0 &&
	ident[EI_MAG1] == ELFMAG1 &&
	ident[EI_MAG2] == ELFMAG2 &&
	ident[EI_MAG3] == ELFMAG3)
		return (1);
	return (0);
}

int	print_error(const int opt, const char *err, const char *filename)
{
	if (opt == 0)
		dprintf(2, "objdump: %s: ", filename);
	else
		dprintf(2, "mmap: ");
	dprintf(2, err);
	return (0);
}
