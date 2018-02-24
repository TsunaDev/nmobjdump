/*
** EPITECH PROJECT, 2018
** nmobjdump
** File description:
** Function that reallocs and concat a string with another
*/

#include <string.h>
#include <stdlib.h>

char	*strcat_realloc(char *dest, char *str)
{
	char	*new = malloc(sizeof(char) * (strlen(dest) +
					strlen(str) + 1));
	size_t	n_idx = 0;

	if (!new)
		return (NULL);
	for (size_t idx = 0; dest[idx]; idx++) {
		new[n_idx] = dest[idx];
		n_idx++;
	}
	for (size_t idx = 0; str[idx]; idx++) {
		new[n_idx] = str[idx];
		n_idx++;
	}
	new[n_idx] = 0;
	free(dest);
	return (new);
}
