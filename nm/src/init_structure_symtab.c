/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** functions to init symtab in elf32 and elf64 structs
*/

#include <string.h>
#include "nm.h"

void	set_64bits_symtab(void *data, elf64_t *elf)
{
	char	*shstrtab = (char *)(data + elf->sections
				[elf->header->e_shstrndx].sh_offset);

	for (size_t idx = 0; idx < elf->header->e_shnum; idx++) {
		if (!strcmp(&shstrtab[elf->sections[idx].sh_name], ".symtab"))
			elf->shsymtab = &(elf->sections[idx]);
		if (!strcmp(&shstrtab[elf->sections[idx].sh_name], ".strtab"))
			elf->shstrtab = &(elf->sections[idx]);
	}
	if (elf->shsymtab)
		elf->symtab = (Elf64_Sym *)((char *)data +
				elf->shsymtab->sh_offset);
	if (elf->shstrtab)
		elf->symtab_str = (char *)((char *)data + elf->shstrtab->
						sh_offset);
}

void	set_32bits_symtab(void *data, elf32_t *elf)
{
	char	*shstrtab = (char *)(data + elf->sections
				[elf->header->e_shstrndx].sh_offset);

	for (size_t idx = 0; idx < elf->header->e_shnum; idx++) {
		if (!strcmp(&shstrtab[elf->sections[idx].sh_name], ".symtab"))
			elf->shsymtab = &(elf->sections[idx]);
		if (!strcmp(&shstrtab[elf->sections[idx].sh_name], ".strtab"))
			elf->shstrtab = &(elf->sections[idx]);
	}
	if (elf->shsymtab)
		elf->symtab = (Elf32_Sym *)((char *)data +
				elf->shsymtab->sh_offset);
	if (elf->shstrtab)
		elf->symtab_str = (char *)((char *)data + elf->shstrtab->
						sh_offset);
}

