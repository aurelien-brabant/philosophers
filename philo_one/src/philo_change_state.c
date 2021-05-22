#include <stdio.h>
#include <pthread.h>

#include "philo_one.h"

static void	handle_philosopher_death(t_philosopher *philo)
{
	t_philosopher	*cur;

	cur = philo;
	while (cur->id > 1)
	{
		cur->state = PHILO_STATE_DEAD;
		cur = cur->left_philo;
	}
	cur = philo;
	while (cur->id <= philo->params[NUMBER_OF_PHILOSOPHERS])
	{
		cur->state = PHILO_STATE_DEAD;
		cur = cur->left_philo;
	}
}

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
	printf("%lldms %lld %s\n", get_timestamp(), philo->id, get_state_string(new_state));	
	philo->state = new_state;
	pthread_mutex_unlock(&philo->mutexes[PHILO_ONE_PRINTF_MUTEX]);
}
