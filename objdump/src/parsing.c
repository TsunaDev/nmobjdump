/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Various parsing functions
*/

#include <stdlib.h>
#include <stdio.h>

char	*get_format(size_t size)
{
	unsigned int	quotient = (unsigned int)size;
	int		count = 0;
	char		*ret;
	int		check;

	while (quotient != 0) {
		quotient /= 16;
		count++;
	}
	if (count < 4)
		count = 4;
	check = asprintf(&ret, " %%0%dx", count);
	return ((check != -1) ? ret : NULL);
}
