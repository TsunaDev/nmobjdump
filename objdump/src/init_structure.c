/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Functions to init the elf structure
*/

#include <sys/stat.h>
#include <sys/mman.h>
#include "objdump.h"
#include "errors.h"

static void	set_64bits_struct(elf_t *elf)
{
	elf->elf64 = malloc(sizeof(elf64_t));
	elf->elf32 = NULL;
	elf->elf64->header = (Elf64_Ehdr *)elf->data;
	elf->elf64->sections = (Elf64_Shdr *)(elf->data +
					elf->elf64->header->e_shoff);
	elf->class = ELFCLASS64;
}

static void	set_32bits_struct(elf_t *elf)
{
	elf->elf32 = malloc(sizeof(elf32_t));
	elf->elf64 = NULL;
	elf->elf32->header = (Elf32_Ehdr *)elf->data;
	elf->elf32->sections = (Elf32_Shdr *)(elf->data +
					elf->elf32->header->e_shoff);
	elf->class = ELFCLASS32;
}

int	get_elf(const int fd, elf_t *elf, const char *filename)
{
	struct stat	s;
	Elf32_Ehdr	*tmp;

	fstat(fd, &s);
	elf->data = mmap(NULL, s.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (elf->data == MAP_FAILED)
		return (print_error(1, "Map failed\n", filename));
	tmp = (Elf32_Ehdr *)elf->data;
	if (!check_magic_number(tmp->e_ident))
		return (print_error(0, "File format not recognized\n", filename));
	if (tmp->e_ident[EI_CLASS] == ELFCLASS32)
		set_32bits_struct(elf);
	else if (tmp->e_ident[EI_CLASS] == ELFCLASS64)
		set_64bits_struct(elf);
	else
		return (print_error(0, "Unknown class\n", filename));
	if (is_truncated(elf, s.st_size))
		return (print_error(0, "File truncated\n", filename));
	return (1);
}
