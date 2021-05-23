#include <unistd.h>

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
	while (*philo->waiting_for_threads)
		;
	philo->last_meal_timestamp = 0;
	while (*philo->health_check)
	{
		if (get_timestamp() - philo->last_meal_timestamp > philo->params[TIME_TO_DIE])
			philo_change_state(philo, PHILO_STATE_DEAD);
	}
	return (philo);
}
