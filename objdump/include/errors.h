/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Error management and print header
*/

#ifndef	ERRORS_H_
#define ERRORS_H_

int	is_truncated(elf_t *, size_t);
int	check_magic_number(unsigned char ident[]);
int	print_error(const int, const char *, const char *);

#endif	/* !ERRORS_H_ */
