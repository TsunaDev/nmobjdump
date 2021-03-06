/*
** EPITECH PROJECT, 2018
** nm/objdump
** File description:
** objdump main functions for 64bits architecture elf files
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objdump.h"
#include "parsing.h"

static void	dump_line(Elf64_Shdr *sections, char *section, size_t off)
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

static void	dump_section(Elf64_Shdr *sections, char *section)
{
	char	*fmt = get_format(sections->sh_size);

	for (size_t offset = 0; offset < sections->sh_size;
	offset += LINE_SIZE) {
		printf(fmt, (unsigned)(sections->sh_addr + offset));
		dump_line(sections, section, offset);
	}
	free(fmt);
}

static int	is_eligible_to_dump(char *name, uint32_t type)
{
	if (type != SHT_NOBITS && type != SHT_SYMTAB &&
	(type != SHT_RELA || !strcmp(name, ".rela.dyn") ||
	!strcmp(name, ".rela.plt")) && strcmp(name, ".strtab"))
		return (1);
	return (0);
}

static void	print_info(void *data, const char *elf_file, elf64_t *elf)
{
	char	*flags_string = malloc(sizeof(char));
	size_t	flags = get_flags64(data, elf, &flags_string);

	printf("\n%s:     file format elf64-x86-64\n", elf_file);
	printf("architecture: %s, flags 0x%08lx:\n",
	(elf->header->e_machine == EM_X86_64) ? "i386:x86-64" : "unknown",
	(flags));
	printf("%s\n", flags_string);
	free(flags_string);
	printf("start address 0x%016lx\n\n", elf->header->e_entry);
}

void	dump_sections64(void *data, elf64_t *elf, const char *file)
{
	void	*section;
	char	*shstrtab = data +
		elf->sections[elf->header->e_shstrndx].sh_offset;

	print_info(data, file, elf);
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
