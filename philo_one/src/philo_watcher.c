#include <stdio.h>
#include <unistd.h>

#include "philo_one.h"

/*
** is_philosopher_healthy
**
** Ensure that the philosopher is not starving. If he is, then the simulation
** needs to stop as soon as possible
**
** @param	philo	the address of the philosopher which is checked.
**
** @return	a boolean which indicates whether or not the philosopher is alive.
*/

static bool	is_philosopher_healthy(t_philosopher *philo)
{
	if (get_timestamp() >= philo->last_meal_timestamp + get_params()[TIME_TO_DIE])
	{
		philo_change_state(philo, PHILO_STATE_DEAD);
		return (false);
	}
	return (true);
}

/*
static void	check_sync(t_philosopher *philosophers)
{
	unsigned long long	i;

	i = 0;
	while (i < get_params()[NUMBER_OF_PHILOSOPHERS])
	{
		if (i == 0)
		i += 2;	
	}
	*philosophers[0].synced = true;
}
*/

/*
** philo_watcher
**
** The watcher is represented by a seperated thread, which is constantly
** ensuring that the simulation can still run. 
**
** It is responsible of killing a philosopher that did not eat during
** time_to_die miliseconds, or to stop the simulation when all the 
** philosophers have eaten at least the required amount of times (only if this
** information is supplied).
**
** @param	the argument passed to pthread_create, which is the array of philosophers.
**
** @return	the same array of philosophers. The return value is not used.
*/

void	*philo_watcher(t_philosopher *philosophers)
{
	unsigned long long	i;
	unsigned long long	nb_of_full_philo;
	unsigned long long	nb_of_philo;

	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	nb_of_full_philo = 0;
	i = 0;
	while (1)
	{
		if (!is_philosopher_healthy(&philosophers[i]))
			break ;
		if (philosophers[i].eat_count >= get_params()[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT])
		{
			if (++nb_of_full_philo == nb_of_philo)
				break ;
		}
		if (++i == nb_of_philo)
		{
			nb_of_full_philo = 0;
			i = 0;
			usleep(1000);
		}
	}
	*philosophers[0].health_check = false;
	return (philosophers);
}
