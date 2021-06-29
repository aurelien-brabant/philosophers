#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "philo_bonus.h"

static void	exit_child_process(t_philosopher *philo, int exit_code)
{
	sem_close(philo->sem_state);
	sem_close(philo->sem_fork);
	free(philo->philosophers);
	exit(exit_code);
}

static void	*spawn_watcher(t_philosopher *philo)
{
	unsigned long long	time_to_die;

	time_to_die = philo->params[TIME_TO_DIE];
	while (philo->is_at_table)
	{
		if (get_timestamp() >= philo->last_meal_ts + time_to_die)
		{
			philo->is_at_table = false;
			philo_change_state(philo, PHILO_STATE_DEAD);
			exit_child_process(philo, EXIT_CHILD_DIED);
		}
		usleep(1000);
	}
	return (NULL);
}

static void	philo_routine_loop(t_philosopher *philo)
{
	philo->is_at_table = true;
	while (1)
	{
		philo_routine_eat(philo);
		if (philo->eat_count >= philo->params[MAX_EAT_COUNT])
		{
			philo->is_at_table = false;
			break ;
		}
		philo_routine_sleep(philo);
		philo_routine_think(philo);
		usleep(100);
	}
}

/*
** Spawn a philosopher, making him live until he spends time_to_die ms without
** eating.
**
** If there's only one philosopher and therefore only one fork available, then
** the philosopher is not going to take any fork and will just die at
** time_to_die ms.
*/

void	spawn_philosopher(t_philosopher *philo)
{
	pthread_t	watcher;

	philo->sem_state = sem_open(SEM_NM_STATE, 0);
	philo->sem_fork = sem_open(SEM_NM_FORK, 0);
	if (pthread_create(&watcher, NULL, (void *)(void *)&spawn_watcher,
		philo) != 0)
	{
		philo_error_print(ERROR_THREAD_CREATE);
		exit_child_process(philo, EXIT_CHILD_DIED);
	}
	philo_routine_loop(philo);
	pthread_join(watcher, NULL);
	exit_child_process(philo, EXIT_CHILD_HAS_EATEN);
}
