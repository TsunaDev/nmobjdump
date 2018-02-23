/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** objdump header file containing its structure
*/

#ifndef	OBJDUMP_H_
#define	OBJDUMP_H_

#include <elf.h>
#include <stdlib.h>

extern const size_t	LINE_SIZE;

typedef	struct	elf64 {
	Elf64_Ehdr	*header;
	Elf64_Shdr	*sections;
}		elf64_t;

typedef struct	elf32 {
	Elf32_Ehdr	*header;
	Elf32_Shdr	*sections;
}		elf32_t;

typedef struct	elf {
	void		*data;
	char		class;
	size_t		size;
	const char	*filename;
	elf64_t		*elf64;
	elf32_t		*elf32;
}		elf_t;

int	get_elf(const char *, const int, elf_t *);
size_t	get_flags32(void *, elf32_t *, char **);
size_t	get_flags64(void *, elf64_t *, char **);
void	dump_sections32(void *, elf32_t *, const char *);
void	dump_sections64(void *, elf64_t *, const char *);
char	dump_byte(char, int);

#endif	/* !OBJDUMP_H_ */
