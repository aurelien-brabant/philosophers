#include <stdio.h>
#include <unistd.h>

#include "philo_one.h"

void	*philo_watcher(t_philosopher *philo)
{
	unsigned long long	ts;
	while (1)
	{
		ts = get_timestamp(false);
		if (ts >= philo->last_meal_timestamp + philo->params[TIME_TO_DIE])
		{
			philo_change_state(philo, PHILO_STATE_DEAD, &ts);
			*philo->health_check = false;
			break ;
		}
		philo = philo->right_philo;
	}
	return (philo);
}
