/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** functions to check that an elf file has been truncated or not
*/

#include "nm.h"

static int	truncated_64bits(elf64_t *elf, size_t file_size)
{
	if (elf->header->e_shoff > file_size)
		return (1);
	for (size_t idx = 0; idx < elf->header->e_shnum; idx++) {
		if (!(elf->sections[idx].sh_type == SHT_NOBITS) &&
		elf->sections[idx].sh_offset +
		elf->sections[idx].sh_size > file_size)
			return (1);
	}
	return (0);
}

static int	truncated_32bits(elf32_t *elf, size_t file_size)
{
	if (elf->header->e_shoff > file_size)
		return (1);
	for (size_t idx = 0; idx < elf->header->e_shnum; idx++) {
		if (!(elf->sections[idx].sh_type == SHT_NOBITS) &&
		elf->sections[idx].sh_offset +
		elf->sections[idx].sh_size > file_size)
			return (1);
	}
	return (0);
}

int	is_truncated(elf_t *elf, size_t file_size)
{
	if (elf->class == ELFCLASS64)
		return (truncated_64bits(elf->elf64, file_size));
	else if (elf->class == ELFCLASS32)
		return (truncated_32bits(elf->elf32, file_size));
	else
		return (1);
}
