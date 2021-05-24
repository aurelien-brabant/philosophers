#include <stdio.h>
#include <unistd.h>

#include "philo_one.h"

void	*philo_watcher(t_philosopher *philosophers)
{
	unsigned long long	i;
	unsigned long long	philo_nb;
	unsigned long long	time_to_die;

	i = 0;
	philo_nb = get_params()[NUMBER_OF_PHILOSOPHERS];
	time_to_die = get_params()[TIME_TO_DIE];
	while (i < philo_nb)
	{
		if (get_timestamp(false) >= philosophers[i].last_meal_timestamp + time_to_die)
		{
			philo_change_state(&philosophers[i], PHILO_STATE_DEAD, NULL);
			*philosophers[i].health_check = false;
			break ;
		}
		if (++i == philo_nb)
			i = 0;
	}
	return (philosophers);
}
