#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "philo_three.h"

static void	exit_child_process(t_philosopher *philo, int exit_code)
{
	free(philo->philosophers);
	semaphores_close();
	exit(exit_code);
}

static void	*spawn_watcher(t_philosopher *philo)
{
	sem_t	*state_sem;
	unsigned long long	time_to_die;

	state_sem = get_semaphores()[PHILO_THREE_SEM_STATE];
	time_to_die = get_params()[TIME_TO_DIE];
	while (philo->is_at_table)
	{
		if (get_timestamp() >= philo->last_meal_timestamp + time_to_die)
		{
			philo->is_at_table = false;
			ft_sem_wait(state_sem);
			philo_change_state(philo, PHILO_STATE_DEAD);
			exit_child_process(philo, EXIT_CHILD_DIED);
		}
		usleep(100);
	}
	return (NULL);
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
	pthread_t			watcher;
	unsigned long long	max_eat;

	philo->is_at_table = true;
	max_eat = get_params()[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT];
	pthread_create(&watcher, NULL, (void *)(void *)&spawn_watcher, philo);
	while (1)
	{
		philo_routine_eat(philo);
		/*
		if (philo->eat_count >= max_eat)
		{
			philo->is_at_table = false;
			break ;
		}
		*/
		philo_routine_sleep(philo);
		philo_routine_think(philo);
		usleep(100);
	}
	pthread_join(watcher, NULL);
	exit_child_process(philo, EXIT_CHILD_HAS_EATEN);
}
