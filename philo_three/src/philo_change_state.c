#include <stdio.h>
#include <pthread.h>

#include "philo_three.h"

/*
** Change the current state of a philosopher, outputing the change on STDOUT.
*/

void	philo_change_state(t_philosopher *philo, t_philo_state new_state)
{
	philo->state = new_state;
	output_status(get_state_string(philo->state), philo);
}
