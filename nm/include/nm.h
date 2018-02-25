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
	char		*strtab;
}		elf64_t;

typedef struct	elf32 {
	Elf32_Ehdr	*header;
	Elf32_Shdr	*sections;
	Elf32_Shdr	*shsymtab;
	Elf32_Shdr	*shstrtab;
	Elf32_Sym	*symtab;
	char		*strtab;
}		elf32_t;

typedef struct	elf {
	void		*data;
	char		class;
	size_t		size;
	const char	*filename;
	elf64_t		*elf64;
	elf32_t		*elf32;
}		elf_t;

int	get_elf(const char *, const int, elf_t *, int);
void	set_32bits_symtab(void *, elf32_t *);
void	set_64bits_symtab(void *, elf64_t *);
void	dump_symbols32(void *, elf32_t *);
void	dump_symbols64(void *, elf64_t *);
char	get_flags32(Elf32_Sym *, Elf32_Shdr *, char *);
char	get_flags64(Elf64_Sym *, Elf64_Shdr *, char *);

#endif	/* !NM_H_ */
