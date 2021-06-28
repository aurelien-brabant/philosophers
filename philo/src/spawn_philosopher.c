#include <unistd.h>
#include <stdio.h>

#include "philo_one.h"
#include "lib.h"

/*
 ** Spawn a philosopher, making him live until he spends time_to_die ms without
 ** eating.
 **
 ** If there's only one philosopher and therefore only one fork available, then
 ** the philosopher is not going to take any fork and will just die at
 ** time_to_die ms.
 */

void	*spawn_philosopher(t_philosopher *philo)
{
	unsigned long long	philo_nb;

	philo_nb = get_params()[NUMBER_OF_PHILOSOPHERS];
	while (philo_nb == 1 && *philo->health_check)
		usleep(100);
	while (*philo->health_check)
	{
		philo_routine_eat(philo);
		philo_routine_sleep(philo);
		philo_routine_think(philo);
		usleep(100);
	}
	return (philo);
}
