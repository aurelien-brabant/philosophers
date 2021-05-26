#include <unistd.h>
#include <stdio.h>

#include "philo_one.h"
#include "lib.h"

static void	try_to_take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&get_mutexes()[PHILO_ONE_ARBITRATOR_MUTEX]);
	if (!philo->left_fork->owner && !philo->right_fork->owner)
	{
		take_fork(philo, philo->left_fork);
		take_fork(philo, philo->right_fork);
	}
	pthread_mutex_unlock(&get_mutexes()[PHILO_ONE_ARBITRATOR_MUTEX]);
}

static void	drop_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&get_mutexes()[PHILO_ONE_ARBITRATOR_MUTEX]);
	drop_fork(philo->left_fork);
	drop_fork(philo->right_fork);
	pthread_mutex_unlock(&get_mutexes()[PHILO_ONE_ARBITRATOR_MUTEX]);
}

static bool	is_ready_to_eat(t_philosopher *philo)
{
	return (philo->left_fork->owner == philo->id && philo->right_fork->owner == philo->id);
}

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
		try_to_take_forks(philo);
		if (is_ready_to_eat(philo))
		{
			philo_change_state(philo, PHILO_STATE_EATING);
			philo->last_meal_timestamp = get_timestamp();
			philo->eat_count++;
			ft_usleep(time_to_eat);
			drop_forks(philo);
			philo_change_state(philo, PHILO_STATE_SLEEPING);
			ft_usleep(time_to_sleep);
		}
	}
	return (philo);
}
