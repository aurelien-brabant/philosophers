#include <stdlib.h>

#include "lib.h"
#include "philo_one.h"

t_fork	*forks_init(void)
{
	t_fork				*forks;
	unsigned long long	i;
	unsigned long long	nb_of_philo;

	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	forks = malloc(sizeof(*forks) * nb_of_philo);
	if (forks == NULL)
		return (NULL);
	i = 0;
	while (i < nb_of_philo)
	{
		forks[i].id = i + 1;
		forks[i].owner = FORK_NOT_OWNED;
		pthread_mutex_init(&forks[i].mutex, NULL);
		++i;
	}
	return (forks);
}

/*
** Initialize the array of philosophers.
** The number of philosophers is given by the nb_of_philo argument which is
** parsed from the command line.
**
** Forks are allocated and their mutex is initialized.
**
** NULL is returned in case of error (malloc failure is the only one possible).
** Cleanup is automatically handled in case of error.
*/

t_philosopher	*philosophers_init(void)
{
	t_philosopher	*philosophers;
	unsigned long long	nb_of_philo;
	unsigned long long	i;

	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	philosophers = malloc(sizeof (*philosophers) * nb_of_philo);
	if (philosophers == NULL)
		return (NULL);
	i = 0;
	while (i < nb_of_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].last_meal_timestamp = 0;
		philosophers[i].state = PHILO_STATE_THINKING; 
		philosophers[i].eat_count = 0;
		++i;
	}
	return (philosophers);
}
