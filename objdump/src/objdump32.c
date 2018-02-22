/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** specific functions for 32 bits architecture files
*/

#include <stdio.h>
#include <string.h>
#include "parsing.h"
#include "objdump.h"

static void	dump_line(Elf32_Shdr *sections, char *section, size_t off)
{
	char	buffer[LINE_SIZE + 1];

	for (size_t idx = 0; idx < 16; idx += 4) {
		printf(" ");
		for (size_t bit = 0; bit < 4; bit++) {
			buffer[idx + bit] =
				dump_byte(section[off + idx + bit],
					off + idx + bit < sections->sh_size);
		}
	}
	buffer[LINE_SIZE] = 0;
	printf("  %s\n", buffer);
}

static void	dump_section(Elf32_Shdr *sections, char *section)
{
	char	*fmt = get_format(sections->sh_size);

	for (size_t offset = 0; offset < sections->sh_size;
	offset += LINE_SIZE) {
		printf(fmt, (unsigned)(sections->sh_addr + offset));
		dump_line(sections, section, offset);
	}
}

static int	is_eligible_to_dump(char *name, uint32_t type)
{
	if (type != SHT_NOBITS && type != SHT_SYMTAB &&
	(type != SHT_REL || !strcmp(name, ".rel.dyn") ||
	!strcmp(name, ".rel.plt")) && strcmp(name, ".strtab"))
		return (1);
	return (0);
}

void	dump_sections32(void *data, elf32_t *elf)
{
	void	*section;
	char	*shstrtab = data +
		elf->sections[elf->header->e_shstrndx].sh_offset;

	for (size_t idx = 0; idx < elf->header->e_shnum; idx++) {
		section = data + elf->sections[idx].sh_offset;
		if (section == shstrtab)
			break;
		if (shstrtab[elf->sections[idx].sh_name] &&
		is_eligible_to_dump(&shstrtab[elf->sections[idx].sh_name],
				    elf->sections[idx].sh_type)) {
			printf("Contents of section %s:\n",
			&shstrtab[elf->sections[idx].sh_name]);
			dump_section(&(elf->sections[idx]), section);
		}
	}
}
