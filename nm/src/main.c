/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Main functions file for nm
*/

#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "nm.h"
#include "errors.h"

const size_t	LINE_SIZE = 16;

static int	print_file_info(const char *prog, const int fd,
				const char *filename, int ac)
{
	elf_t	elf;

	elf.filename = filename;
	if (!get_elf(prog, fd, &elf, ac))
		return (0);
	if (elf.class == ELFCLASS32) {
//		dump_symbols32(elf.data, elf.elf32, filename);
		free(elf.elf32);
	} else if (elf.class == ELFCLASS64) {
		dump_symbols64(elf.data, elf.elf64);
		free(elf.elf64);
	} else
		return (0);
	munmap(elf.data, elf.size);
	return (1);
}

int	default_path(char *prog)
{
	int	fd = open("a.out", O_RDONLY);

	if (fd < 0) {
		print_error(prog, "No such file\n", "a.out", 1);
		return (84);
	}
	if (!print_file_info(prog, fd, "a.out", 1))
		return (84);
	return (0);
}

int	main(int ac, char **av)
{
	int	fd;
	int	ret = 0;

	if (ac == 1)
		return (default_path(av[0]));
	for (size_t idx = 1; idx < (size_t)ac; idx++) {
		fd = open(av[idx], O_RDONLY);
		if (fd < 0) {
			print_error(av[0], "No such file\n", av[idx], 1);
			ret = 84;
		} else if (!print_file_info(av[0], fd, av[idx], ac))
			ret = 84;
		if (fd >= 0)
			close(fd);
	}
	return (ret);
}
