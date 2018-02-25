/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** nm's main function for 64 bits architecture
*/

#include <stdio.h>
#include "nm.h"


static void	dump_symbol64(void *data, elf64_t *elf, size_t idx)
{
	char	*shstrtab = (char *)(data + elf->sections
				[elf->header->e_shstrndx].sh_offset);
	char	flag;

	if (elf->symtab[idx].st_name != 0 &&
	elf->symtab[idx].st_name != 1 &&
	elf->symtab[idx].st_info != 4) {
		flag = get_flags64(&(elf->symtab[idx]), elf->sections,
				shstrtab);
		if (flag != 'U' && flag != 'w')
			printf("%016lx ", elf->symtab[idx].st_value);
		else
			printf("%16c ", ' ');
		printf("%c", flag);
		printf(" %s\n", &(elf->strtab)[elf->symtab[idx].st_name]);
	}
}

void	dump_symbols64(void *data, elf64_t *elf)
{
	size_t	size = elf->shsymtab->sh_size / sizeof(*(elf->symtab));

	for (size_t idx = 0; idx < size; idx++) {
		dump_symbol64(data, elf, idx);
	}
}
