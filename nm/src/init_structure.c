/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Functions to init the elf structure
*/

#include <sys/stat.h>
#include <sys/mman.h>
#include "nm.h"
#include "errors.h"

static int	set_64bits_struct(elf_t *elf, const char *prog)
{
	elf->elf64 = malloc(sizeof(elf64_t));
	elf->elf32 = NULL;
	elf->elf64->header = (Elf64_Ehdr *)elf->data;
	elf->elf64->sections = (Elf64_Shdr *)(elf->data +
					elf->elf64->header->e_shoff);
	elf->elf64->shsymtab = NULL;
	elf->elf64->shstrtab = NULL;
	set_64bits_symtab(elf->data, elf->elf64);
	elf->class = ELFCLASS64;
	if (!elf->elf64->shsymtab || !elf->elf64->shstrtab)
		return (print_error(prog, "no symbols\n", elf->filename, 0));
	return (1);
}

static int	set_32bits_struct(elf_t *elf, const char *prog)
{
	elf->elf32 = malloc(sizeof(elf32_t));
	elf->elf64 = NULL;
	elf->elf32->header = (Elf32_Ehdr *)elf->data;
	elf->elf32->sections = (Elf32_Shdr *)(elf->data +
					elf->elf32->header->e_shoff);
	elf->elf32->shsymtab = NULL;
	elf->elf32->shstrtab = NULL;
	set_32bits_symtab(elf->data, elf->elf32);
	elf->class = ELFCLASS32;
	if (!elf->elf32->shsymtab || !elf->elf32->shstrtab)
		return (print_error(prog, "no symbols\n", elf->filename, 0));
	return (1);
}

static int	manage_file(elf_t *elf, Elf32_Ehdr *tmp, const char *prog)
{
	int	ret = 1;

	if (tmp->e_ident[EI_CLASS] == ELFCLASS32)
		ret = set_32bits_struct(elf, prog);
	else if (tmp->e_ident[EI_CLASS] == ELFCLASS64)
		ret = set_64bits_struct(elf, prog);
	else
		return (print_error(prog, "Unknown class\n",
				elf->filename, 0));
	if (!ret)
		return (0);
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
