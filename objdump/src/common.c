/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Common function between 32 and 64 bits architecture
*/

#include <stdio.h>
#include <ctype.h>

char	dump_byte(char b, int check)
{
	if (check) {
		printf("%02x", (unsigned char)b);
		return ((isprint(b)) ? b : '.');
	} else {
		printf("  ");
		return (' ');
	}
}
