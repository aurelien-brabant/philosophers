#include "lib.h"

unsigned long long	*get_params(void)
{
	static unsigned long long params[PHILO_PARAM_MAX];

	return (params);
}
