#include <unistd.h>

#include "philo/lib.h"

int	error_out(const char *msg, int exit_code)
{
	dputs(msg, STDERR_FILENO);
	return (exit_code);
}
