#include "philo_one.h"
#include "lib.h"

void	*spawn_philosopher(t_philosopher *philo)
{
	philo->last_meal_timestamp = get_timestamp();
	while (philo->state != PHILO_STATE_DEAD)
	{
		if (get_timestamp() - philo->last_meal_timestamp > philo->params[TIME_TO_DIE])
			philo_change_state(philo, PHILO_STATE_DEAD);
	}
	return (philo);
}
