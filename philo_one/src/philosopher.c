#include <unistd.h>
#include <stdio.h>

#include "philo_one.h"
#include "lib.h"

/*
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
*/

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
