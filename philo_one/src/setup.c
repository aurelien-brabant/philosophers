#include <stdlib.h>

#include "philo_one.h"

static void	give_forks(t_philosopher *philo, t_fork *forks)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	left_fork = &forks[philo->id - 1];
	right_fork = &forks[philo->id % get_params()[NUMBER_OF_PHILOSOPHERS]];
	if (philo->id % 2 == 0)
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
		pthread_mutex_init(&forks[i++], NULL);
	return (forks);
}

t_philosopher	*philosophers_init(void)
{
	t_philosopher	*philosophers;
	t_fork			*forks;
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
