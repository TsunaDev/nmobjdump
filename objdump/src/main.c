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

int	default_path(void)
{
	int	fd = open("a.out", O_RDONLY);

	if (fd < 0) {
		print_error(0, "Can't open file\n", "a.out");
		return (84);
	}
	if (!print_file_info(fd, "a.out"))
		return (84);
	return (0);
}

int	main(int ac, char **av)
{
	int	fd;
	int	ret = 0;

	if (ac == 1)
		return (default_path());
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
