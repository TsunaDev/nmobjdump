/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** 64 bits architecture flags management for file infos
*/

#include <elf.h>
#include <string.h>
#include "objdump.h"
#include "parsing.h"

static size_t	has_reloc(void *data, elf64_t *elf, char **str)
{
	char	*shstrtab = data +
		elf->sections[elf->header->e_shstrndx].sh_offset;

	for (size_t idx = 0; idx < elf->header->e_shnum; idx++) {
		if (elf->sections[idx].sh_type == SHT_RELA &&
		strcmp(&shstrtab[elf->sections[idx].sh_name], ".rela.dyn") &&
		strcmp(&shstrtab[elf->sections[idx].sh_name], ".rela.plt")) {
			*str = strcat_realloc(*str, "HAS_RELOC, ");
			return (0x01);
		}
	}
	return (0x00);
}

static size_t	has_syms(elf64_t *elf, char **str)
{
	for (size_t idx = 0; idx < elf->header->e_shnum; idx++) {
		if (elf->sections[idx].sh_type == SHT_SYMTAB) {
			*str = strcat_realloc(*str, "HAS_SYMS, ");
			return (0x10);
		}
	}
	return (0x00);
}

size_t	get_flags64(void *data, elf64_t *elf, char **str)
{
	size_t	flags = 0x00;

	(*str)[0] = 0;
	flags += has_reloc(data, elf, str);
	if (elf->header->e_type == ET_EXEC) {
		*str = strcat_realloc(*str, "EXEC_P, ");
		flags += 0x02;
	}
	flags += has_syms(elf, str);
	if (elf->header->e_type == ET_DYN) {
		*str = strcat_realloc(*str, "DYNAMIC, ");
		flags += 0x40;
	}
	if (elf->header->e_phnum != 0) {
		*str = strcat_realloc(*str, "D_PAGED, ");
		flags += 0x100;
	}
	if ((*str)[0])
		(*str)[strlen(*str) - 2] = 0;
	return (flags);
}
