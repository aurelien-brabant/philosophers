#include <stdio.h>
#include <pthread.h>

#include "philo_one.h"

static const char	*get_state_string(t_philo_state state)
{
	if (state == PHILO_STATE_EATING)
		return ("is eating");
	if (state == PHILO_STATE_DEAD)
		return ("died");
	if (state == PHILO_STATE_SLEEPING)
		return ("is sleeping");
	if (state == PHILO_STATE_THINKING)
		return ("is thinking");
	return (NULL);
}

void	philo_change_state(t_philosopher *philo, t_philo_state new_state)
{
	pthread_mutex_lock(&philo->mutexes[PHILO_ONE_PRINTF_MUTEX]);
	if (!*philo->health_check)
		return ;
	printf("%lldms %lld %s\n", get_timestamp(), philo->id, get_state_string(new_state));	
	philo->state = new_state;
	if (philo->state == PHILO_STATE_DEAD)
		*philo->health_check = false;
	pthread_mutex_unlock(&philo->mutexes[PHILO_ONE_PRINTF_MUTEX]);
}
