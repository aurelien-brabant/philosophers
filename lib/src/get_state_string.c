#include "lib.h"

const char	*get_state_string(t_philo_state state)
{
	if (state == PHILO_STATE_EATING)
		return (" is eating\n");
	if (state == PHILO_STATE_DEAD)
		return (" \033[1;31mdied\033[0m\n");
	if (state == PHILO_STATE_SLEEPING)
		return (" is sleeping\n");
	if (state == PHILO_STATE_THINKING)
		return (" is thinking\n");
	return (NULL);
}
