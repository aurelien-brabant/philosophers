#include <stdlib.h>

#include "philo_one.h"
#include "philo_error.h"

static void	give_forks(t_philosopher *philo, t_fork *forks)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	left_fork = &forks[philo->id - 1];
	right_fork = &forks[philo->id % get_params()[NUMBER_OF_PHILOSOPHERS]];
	if (philo->id % 2 == 0 || philo->id == get_params()[NUMBER_OF_PHILOSOPHERS])
	{
		philo->first_fork = right_fork;
		philo->second_fork = left_fork;
	}
	else
	{
		philo->first_fork = left_fork;
		philo->second_fork = right_fork;
	}
}

static t_fork	*forks_init(void)
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
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (i-- < 0)
				pthread_mutex_destroy(&forks[i]);
			pthread_mutex_destroy(&forks[i]);
			philo_error_print(ERROR_MUTEX_INIT);
			return (NULL);
		}
		++i;
	}
	return (forks);
}

static void	destroy_forks(t_fork *forks)
{
	unsigned long long	i;
	unsigned long long	nb_of_philo;

	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_mutex_destroy(&forks[i++]) != 0)
			philo_error_print(ERROR_MUTEX_CLOSE);
	}
}

/*
** Free all the allocated memory for philo_one.
** Can be used if an error occured to free what can be free,
** or at the end of the simulation if everything went well.
*/

void	destroy_philo_one(t_philosopher *philosophers)
{
	if (destroy_mutexes() != PHILO_ONE_TOTAL_MUTEX)
		philo_error_print(ERROR_MUTEX_CLOSE);
	destroy_forks(philosophers[0].forks);
	free(philosophers[0].forks);
	free(philosophers[0].health_check);
	free(philosophers);
}

t_philosopher	*philosophers_init(void)
{
	t_philosopher		*philosophers;
	t_fork				*forks;
	unsigned long long	nb_of_philo;
	unsigned long long	i;

	forks = forks_init();
	if (forks == NULL)
		return (NULL);
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	philosophers = malloc(sizeof (*philosophers) * nb_of_philo);
	if (philosophers == NULL)
		return (NULL);
	i = 0;
	while (i < nb_of_philo)
	{
		philosophers[i].forks = forks;
		philosophers[i].id = i + 1;
		philosophers[i].last_meal_timestamp = 0;
		philosophers[i].state = PHILO_STATE_THINKING;
		philosophers[i].eat_count = 0;
		give_forks(&philosophers[i], forks);
		++i;
	}
	return (philosophers);
}
