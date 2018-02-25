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
	unsigned int	nb = sizeof(size);
	int		check;
	char		*ret;

	while (nb > 0 && !((0xf << ((nb - 1) * 4)) & size))
		nb--;
	if (nb < 4)
		nb = 4;
	check = asprintf(&ret, " %%0%dx", nb);
	return ((check != -1) ? ret : NULL);
}
