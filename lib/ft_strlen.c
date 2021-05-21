#include <stddef.h>

/*
** Return the number of characters in a string, encoded in a C fashion, i.e
** terminated by a null byte.
*/

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}
