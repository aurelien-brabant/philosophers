#include "philo_one.h"
#include <stdio.h>

void	*philo_watcher(bool *health_check)
{
	while (*health_check)
		;
	return (health_check);
}
