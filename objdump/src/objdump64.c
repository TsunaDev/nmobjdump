/*
** EPITECH PROJECT, 2018
** nm/objdump
** File description:
** objdump main functions for 64bits architecture elf files
*/

#include <elf.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

char	dump_byte(char b)
{
	printf("%02x", (unsigned char)b);
	return ((isprint(b)) ? b : '.');
}

char	*get_format(size_t size)
{
	unsigned int	quotient = (unsigned int)size;
	int		count = 0;
	char		*ret;
	int		check;

	while(quotient != 0) {
		quotient = quotient / 16;
		count++;
	}
	if (count < 4)
		count = 4;
	check = asprintf(&ret, " %%0%dx", count);
	return ((check != -1) ? ret : NULL);
}

void	dump_section(Elf64_Shdr *sections, char *section)
{
	char	buffer[17];
	char	*fmt = get_format(sections->sh_size);
	size_t	idx = 0;
	size_t	bit;

	for (size_t offset = 0; offset < sections->sh_size; offset += idx) {
		printf(fmt, (unsigned)(sections->sh_addr + offset));
		for (idx = 0; idx < 16; idx += bit) {
			printf(" ");
			for (bit = 0; bit < 4; bit++)
				if (offset + idx + bit < sections->sh_size)
					buffer[idx + bit] = dump_byte(section[offset + idx + bit]);
				else {
					printf("  ");
					buffer[idx + bit] = ' ';
				}
		}
		buffer[16] = 0;
		printf("  %s\n", buffer);
	}
}

int	is_eligible_to_dump(char *name, uint32_t type)
{
	if (type != SHT_NOBITS && type != SHT_SYMTAB &&
	    (type != SHT_RELA || !strcmp(name, ".rela.dyn") ||
	     !strcmp(name, ".rela.plt")) && strcmp(name, ".strtab"))
		return (1);
	return (0);
}

void	dump_sections(Elf64_Shdr *sections, void *data, Elf64_Ehdr *header)
{
	void	*section;
	size_t	idx = 0;
	char	*shstrtab = data + sections[header->e_shstrndx].sh_offset;

	for (size_t idx = 0; idx < header->e_shnum; idx++) {
		section = data + sections[idx].sh_offset;
		if (section == shstrtab)
			break;
		if (shstrtab[sections[idx].sh_name] &&
		    is_eligible_to_dump(&shstrtab[sections[idx].sh_name],
					sections[idx].sh_type)) {
			printf("Contents of section %s:\n",
			       &shstrtab[sections[idx].sh_name]);
			dump_section(&sections[idx], section);
		}
	}
}

int	check_magic_number(char ident[])
{
	if (ident[EI_MAG0] == ELFMAG0 &&
	    ident[EI_MAG1] == ELFMAG1 &&
	    ident[EI_MAG2] == ELFMAG2 &&
	    ident[EI_MAG3] == ELFMAG3)
		return (1);
	return (0);
}

void	print_info(char *elf_file, Elf64_Ehdr *header)
{
	printf("%s:     file format\n", elf_file);
}

int	is_truncated(Elf64_Ehdr *header, Elf64_Shdr *sections, size_t file_size)
{
	for (size_t idx = 0; idx < header->e_shnum; idx++) {
		if (!(sections[idx].sh_type == SHT_NOBITS) &&
		    sections[idx].sh_offset + sections[idx].sh_size > file_size)
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	Elf64_Ehdr	*header;
	Elf64_Shdr	*sections;
	void		*data;
	struct stat	s;

	if (ac != 2)
		return (84);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (84);
	fstat(fd, &s);
	data = mmap(NULL, s.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (data == MAP_FAILED)
		return (84);
	header = (Elf64_Ehdr *)data;
	if (!check_magic_number(header->e_ident))
		return (84);
	sections = (Elf64_Shdr *)(data + header->e_shoff);
	if (!is_truncated(header, sections, s.st_size)) {
		printf("%d\n", header->e_type);
		dump_sections(sections, data, header);
	} else
		printf("objdump: %s: File truncated\n", av[1]);
	close(fd);
	return (0);
}
