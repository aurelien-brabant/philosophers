#include <unistd.h>

#include "philo/lib.h"

int	dputs(const char *s, int fd)
{
	int	n;

	n = write(fd, s, ft_strlen(s));
	n += write(1, "\n", 1);
	return (n);
}
