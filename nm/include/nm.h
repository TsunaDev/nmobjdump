/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** nm header file containing its structure
*/

#ifndef	NM_H_
#define	NM_H_

#include <elf.h>
#include <stdlib.h>

extern const size_t	LINE_SIZE;

typedef	struct	elf64 {
	Elf64_Ehdr	*header;
	Elf64_Shdr	*sections;
	Elf64_Shdr	*shsymtab;
	Elf64_Shdr	*shstrtab;
	Elf64_Sym	*symtab;
	char		*symtab_str;
}		elf64_t;

typedef struct	elf32 {
	Elf32_Ehdr	*header;
	Elf32_Shdr	*sections;
	Elf32_Shdr	*shsymtab;
	Elf32_Shdr	*shstrtab;
	Elf32_Sym	*symtab;
	char		*symtab_str;
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
void	set_32bits_symtab(void *, elf32_t *);
void	set_64bits_symtab(void *, elf64_t *);

#endif	/* !NM_H_ */
