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

	pthread_mutex_lock(&fork->mutex);	
	available = (fork->state == FORK_STATE_UNUSED);
	pthread_mutex_unlock(&fork->mutex);	
	return (available);
}

bool	take_fork(t_philosopher *philo, t_fork *fork)
{
	bool	ret;

	ret = true;
	pthread_mutex_lock(&fork->mutex);	
	if (fork->state == FORK_STATE_USED)
		ret = false;
	else
	{
		printf("%lldms %lld has taken a fork\n", get_timestamp(true), philo->id);
		fork->state = FORK_STATE_USED;
	}
	pthread_mutex_unlock(&fork->mutex);	
	return (ret);
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);	
	fork->state = FORK_STATE_UNUSED;
	pthread_mutex_unlock(&fork->mutex);	
}
