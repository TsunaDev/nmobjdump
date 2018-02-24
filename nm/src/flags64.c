/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Functions that permit to get the flag of a symbol
*/

#include "nm.h"

static char	check_section_index(Elf64_Sym *sym)
{
	char	ret = '?';

	switch (sym->st_shndx) {
	case SHN_UNDEF:
		ret = 'U';
		break;
	case SHN_ABS:
		ret = 'A';
		break;
	case SHN_COMMON:
		ret = 'C';
		break;
	}
	return (ret);
}

static char	progbits_type(uint64_t flags)
{
	char	ret = '?';

	switch (flags) {
	case SHF_ALLOC:
		ret = 'B';
		break;
	case SHF_ALLOC | SHF_WRITE:
		ret = 'D';
		break;
	case SHF_ALLOC | SHF_EXECINSTR:
		ret = 'T';
	}
	return (ret);
}

static char	check_section_type(Elf64_Sym *sym, Elf64_Shdr *sections)
{
	char	ret = '?';

	switch (sections[sym->st_shndx].sh_type) {
	case SHT_NOBITS:
		if (sections[sym->st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
			ret = 'B';
		break;
	case SHT_PROGBITS:
		ret = progbits_type(sections[sym->st_shndx].sh_flags);
		break;
	case SHT_DYNAMIC:
		ret = 'D';
		break;
	}
	return ret;
}

static char	check_bind(Elf64_Sym *sym, uint64_t bind, uint64_t type)
{
	char	ret = '?';

	switch (bind) {
	case STB_GNU_UNIQUE:
		ret = 'u';
		break;
	case STB_WEAK:
		if (type == STT_OBJECT)
			ret = (sym->st_shndx == SHN_UNDEF) ? 'v' : 'V';
		else
			ret = (sym->st_shndx == SHN_UNDEF) ? 'w' : 'W';
		break;
	}
	return (ret);
}

char get_flags64(Elf64_Sym *sym, Elf64_Shdr *section)
{
	char	c;
	char	b = check_bind(sym, ELF64_ST_BIND(sym->st_info),
			ELF64_ST_TYPE(sym->st_info));

	if (b != '?')
		c = b;
	else {
		c = check_section_index(sym);
		if (c == '?')
			c = check_section_type(sym, section);
	}
	if (ELF64_ST_BIND(sym->st_info) == STB_LOCAL && c != '?')
		c += 32;
	return (c);
}
