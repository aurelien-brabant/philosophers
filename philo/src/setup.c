#include <stdlib.h>

#include "philo.h"

static void	give_forks(t_philosopher *philo, t_fork *forks)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	left_fork = &forks[philo->id - 1];
	right_fork = &forks[philo->id % philo->params[NUMBER_OF_PHILOSOPHERS]];
	if (philo->id % 2 == 0
		|| philo->id == philo->params[NUMBER_OF_PHILOSOPHERS])
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

static t_fork	*forks_init(unsigned int nb_of_philo)
{
	t_fork				*forks;
	unsigned int		i;

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

static void	destroy_forks(t_fork *forks, unsigned int nb_of_philo)
{
	unsigned int	i;

	i = 0;
	while (i < nb_of_philo)
	{
		if (pthread_mutex_destroy(&forks[i++]) != 0)
			philo_error_print(ERROR_MUTEX_CLOSE);
	}
}

void	destroy_simulation(t_philosopher *philosophers)
{
	destroy_forks(philosophers[0].forks,
		philosophers[0].params[NUMBER_OF_PHILOSOPHERS]);
	free(philosophers[0].forks);
	if (pthread_mutex_destroy(philosophers[0].out_mutex) != 0)
			philo_error_print(ERROR_MUTEX_CLOSE);
	free(philosophers[0].out_mutex);
	free(philosophers[0].health_check);
	free(philosophers);
}

t_philosopher	*philosophers_init(unsigned int *params)
{
	t_philosopher	*philosophers;
	t_fork			*forks;
	unsigned int	i;

	forks = forks_init(params[NUMBER_OF_PHILOSOPHERS]);
	if (forks == NULL)
		return (NULL);
	philosophers = malloc(sizeof (*philosophers)
			* params[NUMBER_OF_PHILOSOPHERS]);
	if (philosophers == NULL)
		return (NULL);
	i = 0;
	while (i < params[NUMBER_OF_PHILOSOPHERS])
	{
		philosophers[i].params = params;
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
