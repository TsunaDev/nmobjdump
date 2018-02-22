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
	elf64_t		*elf64;
	elf32_t		*elf32;
}		elf_t;

int	get_elf(const int, elf_t *, const char *);
void	dump_sections32(void *, elf32_t *);
void	dump_sections64(void *, elf64_t *);
char	dump_byte(char, int);

#endif	/* !OBJDUMP_H_ */
