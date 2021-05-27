#include <stdio.h>
#include <pthread.h>

#include "philo_one.h"

/*
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
*/

/*
** Change the current state of a philosopher, outputing the change on STDOUT.
*/

void	philo_change_state(t_philosopher *philo, t_philo_state new_state)
{
	if (*philo->health_check)
	{
		output_status(get_state_string(new_state), philo->id);	
		philo->state = new_state;
	}
}
