#include <stdio.h>
#include <pthread.h>

#include "philo_two.h"

/*
** Change the current state of a philosopher, outputing the change on STDOUT.
*/

void	philo_change_state(t_philosopher *philo, t_philo_state new_state)
{
	sem_wait(get_semaphores()[PHILO_TWO_STATE_SEMAPHORE]);
	if (*philo->health_check)
		philo->state = new_state;
	output_status(get_state_string(philo->state), philo);	
	if (philo->state == PHILO_STATE_DEAD)
		*philo->health_check = false;
	sem_post(get_semaphores()[PHILO_TWO_STATE_SEMAPHORE]);
}
