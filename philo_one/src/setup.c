#include <stdlib.h>

#include "lib.h"
#include "philo_one.h"

/*
** Allocate a new fork and initialize it.
** A mutex is initialized for each allocated fork.
*/

static t_fork	*fork_new()
{
	t_fork	*fork;

	fork = malloc(sizeof (*fork));
	if (fork == NULL)
		return (NULL);
	fork->state = FORK_STATE_UNUSED;
	fork->owner = FORK_NOT_OWNED;
	pthread_mutex_init(&fork->mutex, NULL);
	return (fork);
}

void	*destroy_philosophers(t_philosopher *philosophers)
{
	unsigned long long	i;
	unsigned long long	nb_of_philo;

	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	i = 0;
	while (i < nb_of_philo)
	{
		pthread_mutex_destroy(&philosophers[i].right_fork->mutex);
		free(philosophers[i].right_fork);
		++i;
	}
	free(philosophers);
	return (NULL);
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
		philosophers[i].right_fork = fork_new();
		philosophers[i].right_fork->id = i + 1;
		if (philosophers[i].right_fork == NULL)
			return (destroy_philosophers(philosophers));
		philosophers[i].id = i + 1;
		philosophers[i].last_meal_timestamp = 0;
		philosophers[i].state = PHILO_STATE_THINKING; 
		if (i > 0)
			philosophers[i].left_fork = philosophers[i - 1].right_fork;
		++i;
	}
	philosophers[0].left_fork = philosophers[i - 1].right_fork;
	return (philosophers);
}
