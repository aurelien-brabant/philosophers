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
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;

	time_to_eat = get_params()[TIME_TO_EAT];
	time_to_sleep = get_params()[TIME_TO_SLEEP];
	while (*philo->waiting_for_threads)
		;
	while (*philo->health_check)
	{
		if (philo->left_fork->state == FORK_STATE_UNUSED
			&& philo->right_fork->state == FORK_STATE_UNUSED)
		{
			if (take_fork(philo, philo->left_fork) && take_fork(philo, philo->right_fork))
			{
				philo_change_state(philo, PHILO_STATE_EATING);
				usleep(time_to_eat * 1000);
				drop_fork(philo->left_fork);
				drop_fork(philo->right_fork);
				philo_change_state(philo, PHILO_STATE_SLEEPING);
				usleep(time_to_sleep * 1000);
			}
		}
		usleep(100);
	}
	return (philo);
}
