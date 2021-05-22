#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "philo_one.h"
#include "lib.h"

static void	*spawn_philosopher(t_philosopher *philo)
{
	sleep(1);
	printf("Hello I'm philosopher from thread %llu\n", philo->id);
	return (philo);
}

static void	run_simulation(t_philosopher *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->params[NUMBER_OF_PHILOSOPHERS])
	{
		pthread_create(&philo->thread, NULL, (void *)(void *)&spawn_philosopher, philo);
		pthread_detach(philo->thread);
		philo = philo->right_philo;
		++i;
	}
	sleep(5);
}

int	main(int ac, char **av)
{
	unsigned long long	params[PHILO_PARAM_MAX];
	t_philosopher		*philo;

	if (!parse_params(ac, av, params))
		return (1);
	philo = dress_philosophy_table(params);
	if (philo == NULL)
		return (1);
	run_simulation(philo);
	destroy_philosophers(philo->left_philo);
	return (0);
}
