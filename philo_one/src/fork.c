#include <pthread.h>
#include <stdio.h>

#include "philo_one.h"

bool	is_fork_available(t_fork *fork)
{
	bool	available;

	available = (!fork->owner);
	return (available);
}

bool	take_fork(t_philosopher *philo, t_fork *fork)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&fork->mutex);	
	if (*philo->health_check && fork->owner == FORK_NOT_OWNED)
	{
		ret = true;
		fork->owner = philo->id;
		output_status(" has taken a fork\n", philo->id);
	}
	pthread_mutex_unlock(&fork->mutex);	
	return (ret);
}

void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);	
	fork->owner = FORK_NOT_OWNED;
	pthread_mutex_unlock(&fork->mutex);	
}
