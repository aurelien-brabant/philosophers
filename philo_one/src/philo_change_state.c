#include <stdio.h>
#include <pthread.h>

#include "philo_one.h"

/*
** Change the current state of a philosopher, outputing the change on STDOUT.
*/

void	philo_change_state(t_philosopher *philo, t_philo_state new_state)
{
	pthread_mutex_lock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);
	if (*philo->health_check)
		philo->state = new_state;
	output_status(get_state_string(philo->state), philo);	
	if (philo->state == PHILO_STATE_DEAD)
		*philo->health_check = false;
	pthread_mutex_unlock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);
}
