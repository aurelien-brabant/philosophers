#include <unistd.h>
#include "philo/lib.h"

static bool	output_error(const char *s)
{
	dputs(s, STDERR_FILENO);
	return (false);
}

/*
** Parse a string representing a positive integer. The biggest C type available
** is used, that is unsigned long long. The resulting number is placed in
** the n parameter.
** NOTE: What is stored in the n parameter is not meant to have
** any sense if an error occurs.
**
** @return a boolean which indicates if an error occured. Details about the
** error are outputed on STDERR no matter what.
*/

bool	parse_uint(const char *sint, unsigned long long *n)
{
	unsigned long long	new_val;

	*n = 0;
	while (*sint != '\0')
	{
		new_val = *n * 10 + *sint++ - 48;
		if (new_val < *n)
			return (output_error("parse_uint: overflow detected."));
		*n = new_val;
	}
	return (true);
}
