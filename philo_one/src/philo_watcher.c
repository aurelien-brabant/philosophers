#include <stdio.h>
#include <unistd.h>

#include "philo_one.h"

void	*philo_watcher(bool *health_check)
{
	while (*health_check)
		usleep(1000);
	return (health_check);
}
