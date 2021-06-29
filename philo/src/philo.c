#include <unistd.h>

#include "philo.h"

/*
 ** Spawn a philosopher, making him live until he spends time_to_die ms without
 ** eating.
 **
 ** If there's only one philosopher and therefore only one fork available, then
 ** the philosopher is not going to take any fork and will just die at
 ** time_to_die ms.
 */

void	*spawn_philosopher(t_philosopher *philo)
{
	while (philo->params[NB_PHILO] == 1 && *philo->health_check)
		usleep(100);
	while (*philo->health_check)
	{
		philo_routine_eat(philo);
		philo_routine_sleep(philo);
		philo_routine_think(philo);
		usleep(100);
	}
	return (philo);
}

void	*philo_watcher(t_philosopher *philosophers)
{
	unsigned int	i;
	unsigned int	full;
	t_philosopher	*philo;

	full = 0;
	i = 0;
	while (*philosophers[0].health_check)
	{
		philo = &philosophers[i];
		if (get_timestamp() >= philo->last_meal_ts + philo->params[TIME_TO_DIE])
			philo_change_state(philo, PHILO_STATE_DEAD);
		if (philo->eat_count >= philo->params[MAX_EAT_COUNT]
			&& ++full == philo->params[NB_PHILO])
			*philo->health_check = false;
		else if (++i == philo->params[NB_PHILO])
		{
			full = 0;
			i = 0;
			usleep(1000);
		}
	}
	*philosophers[0].health_check = false;
	return (philosophers);
}

void	philo_routine_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->second_fork);
	pthread_mutex_lock(philo->out_mutex);
	output_status(" has taken a fork\n", philo);
	output_status(" has taken a fork\n", philo);
	pthread_mutex_unlock(philo->out_mutex);
	philo_change_state(philo, PHILO_STATE_EATING);
	philo->last_meal_ts = get_timestamp();
	philo->eat_count++;
	ft_msleep(philo->params[TIME_TO_EAT]);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	philo_routine_sleep(t_philosopher *philo)
{
	philo_change_state(philo, PHILO_STATE_SLEEPING);
	ft_msleep(philo->params[TIME_TO_SLEEP]);
}

void	philo_routine_think(t_philosopher *philo)
{
	philo_change_state(philo, PHILO_STATE_THINKING);
}
