#include <unistd.h>

#include "lib.h"

int	error_out(const char *msg, int error_code)
{
	dputs(msg, STDERR_FILENO);
	return (error_code);
}
