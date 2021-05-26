#include <pthread.h>
#include <stdio.h>

#include "philo_one.h"

bool	are_forks_available(t_philosopher *philo)
{
	return (is_fork_available(philo->left_fork) 
		&& is_fork_available(philo->right_fork));
}

bool	is_fork_available(t_fork *fork)
{
	bool	available;

	available = (!fork->owner);
	return (available);
}

bool	take_fork(t_philosopher *philo, t_fork *fork)
{
	bool	ret;

	ret = true;
	pthread_mutex_lock(&fork->mutex);	
	pthread_mutex_lock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);	
	if (*philo->health_check && !fork->owner)
	{
		printf("%lldms %lld has taken a fork\n", get_timestamp(), philo->id);
		fork->owner = philo->id;
	}
	pthread_mutex_unlock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);	
	pthread_mutex_unlock(&fork->mutex);	
	return (ret);
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);	
	fork->owner = FORK_NOT_OWNED;
	pthread_mutex_unlock(&fork->mutex);	
}
