#include <unistd.h>
#include <stdio.h>

#include "philo_one.h"
#include "lib.h"

/*
** Spawn a philosopher, making him live until he spends time_to_die ms without
** eating.
** Each philosopher, which is a thread, needs to wait for all the others to be ready.
** That's the purpose of the first while loop.
** philo->waiting_for_threads is automatically going to be set to false when all the
** threads will have been created. This is managed by the main thread.
*/

void	*spawn_philosopher(t_philosopher *philo)
{
	while (*philo->health_check)
	{
		philo_routine_eat(philo);
		philo_routine_sleep(philo);
		philo_routine_think(philo);
		usleep(100);
	}
	return (philo);
}
