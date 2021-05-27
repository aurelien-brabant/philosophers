#include <unistd.h>
#include <stdio.h>

#include "philo_one.h"
#include "lib.h"

static bool	try_to_pick_forks(t_philosopher *philo, t_fork *left_fork, t_fork *right_fork)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&get_mutexes()[PHILO_ONE_ARBITRATOR_MUTEX]);
	if (*philo->health_check && !left_fork->owner && !right_fork->owner)
	{
		take_fork(philo, left_fork);
		take_fork(philo, right_fork);
		ret = true;
	}
	pthread_mutex_unlock(&get_mutexes()[PHILO_ONE_ARBITRATOR_MUTEX]);
	return (ret);
}

static void	drop_forks(t_fork *left_fork, t_fork *right_fork)
{
	//pthread_mutex_lock(&get_mutexes()[PHILO_ONE_ARBITRATOR_MUTEX]);
	drop_fork(left_fork);
	drop_fork(right_fork);
	//pthread_mutex_unlock(&get_mutexes()[PHILO_ONE_ARBITRATOR_MUTEX]);
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
	t_fork				*left_fork;
	t_fork				*right_fork;

	time_to_eat = get_params()[TIME_TO_EAT];
	time_to_sleep = get_params()[TIME_TO_SLEEP];
	left_fork = &philo->forks[philo->id - 1];
	right_fork = &philo->forks[philo->id % get_params()[NUMBER_OF_PHILOSOPHERS]];
	while (*philo->waiting_for_threads)
		usleep(10);
	while (*philo->health_check)
	{
		if (left_fork->owner || right_fork->owner)
			usleep(100);
		else if (try_to_pick_forks(philo, left_fork, right_fork))
		{
			philo_change_state(philo, PHILO_STATE_EATING);
			philo->last_meal_timestamp = get_timestamp();
			philo->eat_count++;
			usleep(time_to_eat * 1000);
			drop_forks(left_fork, right_fork);
			philo_change_state(philo, PHILO_STATE_SLEEPING);
			usleep(time_to_sleep * 1000);
			philo_change_state(philo, PHILO_STATE_THINKING);
		} 
	}
	return (philo);
}
