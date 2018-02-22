/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Main functions file for objdump
*/

#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include "objdump.h"
#include "errors.h"

const size_t	LINE_SIZE = 16;

/* static void	set_64bits_struct(elf_t *elf) */
/* { */
/* 	elf->elf64 = malloc(sizeof(elf64_t)); */
/* 	elf->elf32 = NULL; */
/* 	elf->elf64->header = (Elf64_Ehdr *)elf->data; */
/* 	elf->elf64->sections = (Elf64_Shdr *)(elf->data + */
/* 					elf->elf64->header->e_shoff); */
/* 	elf->class = ELFCLASS64; */
/* } */

/* static void	set_32bits_struct(elf_t *elf) */
/* { */
/* 	elf->elf32 = malloc(sizeof(elf32_t)); */
/* 	elf->elf64 = NULL; */
/* 	elf->elf32->header = (Elf32_Ehdr *)elf->data; */
/* 	elf->elf32->sections = (Elf32_Shdr *)(elf->data + */
/* 					elf->elf32->header->e_shoff); */
/* 	elf->class = ELFCLASS32; */
/* } */

/* static int	get_elf(const int fd, elf_t *elf, const char *filename) */
/* { */
/* 	struct stat	s; */
/* 	Elf32_Ehdr	*tmp; */

/* 	fstat(fd, &s); */
/* 	elf->data = mmap(NULL, s.st_size, PROT_READ, MAP_SHARED, fd, 0); */
/* 	if (elf->data == MAP_FAILED) */
/* 		return (print_error(1, "Map failed\n", filename)); */
/* 	tmp = (Elf32_Ehdr *)elf->data; */
/* 	if (!check_magic_number(tmp->e_ident)) */
/* 		return (print_error(0, "File format not recognized\n", filename)); */
/* 	if (tmp->e_ident[EI_CLASS] == ELFCLASS32) */
/* 		set_32bits_struct(elf); */
/* 	else if (tmp->e_ident[EI_CLASS] == ELFCLASS64) */
/* 		set_64bits_struct(elf); */
/* 	else */
/* 		return (print_error(0, "Unknown class\n", filename)); */
/* 	if (is_truncated(elf, s.st_size)) */
/* 		return (print_error(0, "File truncated\n", filename)); */
/* 	return (1); */
/* } */

static int	print_file_info(const int fd, const char *filename)
{
	elf_t	elf;

	if (!get_elf(fd, &elf, filename))
		return (0);
	if (elf.class == ELFCLASS32)
		dump_sections32(elf.data, elf.elf32);
	else if (elf.class == ELFCLASS64)
		dump_sections64(elf.data, elf.elf64);
	else
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	int	fd;
	int	ret = 0;
	char	def_path[6] = "a.out";

	for (size_t idx = 1; idx < (size_t)ac; idx++) {
		fd = open(av[idx], O_RDONLY);
		if (fd < 0) {
			print_error(0, "Can't open file\n", av[idx]);
			ret = 84;
		} else if (!print_file_info(fd, av[idx]))
			ret = 84;
		if (fd >= 0)
			close(fd);
	}
	return (ret);
}
