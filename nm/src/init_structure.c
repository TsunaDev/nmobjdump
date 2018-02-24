/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Functions to init the elf structure
*/

#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include "nm.h"
#include "errors.h"

static void	set_64bits_struct(elf_t *elf)
{
	char	*shstrtab;

	elf->elf64 = malloc(sizeof(elf64_t));
	elf->elf32 = NULL;
	elf->elf64->header = (Elf64_Ehdr *)elf->data;
	elf->elf64->sections = (Elf64_Shdr *)(elf->data +
					elf->elf64->header->e_shoff);
	shstrtab = (char *)(elf->data +
			elf->elf64->sections[elf->elf64->header->e_shstrndx].
			sh_offset);
	for (size_t idx = 0; idx < elf->elf64->header->e_shnum; idx++) {
		if (strcmp(&shstrtab[elf->elf64->sections[idx].sh_name],
			".symtab"))
			elf->elf64->symtab = &(elf->elf64->sections[idx]);
		if (strcmp(&shstrtab[elf->elf64->sections[idx].sh_name],
			".strtab"))
			elf->elf64->strtab = &(elf->elf64->sections[idx]);
	}
	elf->class = ELFCLASS64;
}

static void	set_32bits_struct(elf_t *elf)
{
	char	*shstrtab;

	elf->elf32 = malloc(sizeof(elf32_t));
	elf->elf64 = NULL;
	elf->elf32->header = (Elf32_Ehdr *)elf->data;
	elf->elf32->sections = (Elf32_Shdr *)(elf->data +
					elf->elf32->header->e_shoff);
	shstrtab = (char *)(elf->data +
			elf->elf32->sections[elf->elf32->header->e_shstrndx].
			sh_offset);
	for (size_t idx = 0; idx < elf->elf32->header->e_shnum; idx++) {
		if (strcmp(&shstrtab[elf->elf32->sections[idx].sh_name],
			".symtab"))
			elf->elf32->symtab = &(elf->elf32->sections[idx]);
		if (strcmp(&shstrtab[elf->elf32->sections[idx].sh_name],
			".strtab"))
			elf->elf32->strtab = &(elf->elf32->sections[idx]);
	}
	elf->class = ELFCLASS32;
}

static int	manage_file(elf_t *elf, Elf32_Ehdr *tmp, const char *prog)
{
	if (tmp->e_ident[EI_CLASS] == ELFCLASS32)
		set_32bits_struct(elf);
	else if (tmp->e_ident[EI_CLASS] == ELFCLASS64)
		set_64bits_struct(elf);
	else
		return (print_error(prog, "Unknown class\n",
				elf->filename, 0));
	if (is_truncated(elf, elf->size))
		return (print_error(prog, "File truncated\n",
				elf->filename, 0));
	return (1);
}

int	get_elf(const char *prog, const int fd, elf_t *elf)
{
	struct stat	s;
	Elf32_Ehdr	*tmp;

	fstat(fd, &s);
	if (S_ISDIR(s.st_mode))
		return (print_error(prog, "is a directory\n",
				elf->filename, 2));
	if (s.st_size == 0)
		return (print_error(prog, "File format not recognized\n",
				elf->filename, 0));
	elf->data = mmap(NULL, s.st_size, PROT_READ, MAP_SHARED, fd, 0);
	elf->size = s.st_size;
	if (elf->data == MAP_FAILED)
		return (print_error(prog, "Map failed\n", elf->filename, 0));
	tmp = (Elf32_Ehdr *)elf->data;
	if (!check_magic_number(tmp->e_ident))
		return (print_error(prog, "File format not recognized\n",
				elf->filename, 0));
	return (manage_file(elf, tmp, prog));
}
