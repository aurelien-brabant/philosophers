#include <stdio.h>
#include <pthread.h>

#include "lib.h"

static void	handle_philosopher_death()
{
	
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

/*
** Change the current state of a philosopher. As the philosopher type may be different depending
** on the version, only the required parameters are passed, that are the ID of the philosopher
** (used for the output) and the address of his current state.
**
** The required message is printed on STDOUT using printf to notify the change.
**
** NOTE: taking a fork is a particular operation and does NOT modify the philosopher's
** state in any way. The take_fork library's function can be used for that.
*/

void	philo_change_state(unsigned long long philo_id, t_philo_state *old_state, 
							t_philo_state new_state, pthread_mutex_t *printf_mutex)
{
	printf("%lldms %lld %s\n", get_timestamp(), philo_id, get_state_string(*new_state));	
	*old_state = new_state;
}
