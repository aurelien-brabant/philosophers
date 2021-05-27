#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "philo_one.h"

/*
** Wait for each thread, which is a philosopher, to terminate properly
** before moving on.
*/

static void	terminate_philo_threads(t_philosopher *philosophers)
{
	unsigned long long nb_of_philo;
	unsigned long long i;

	i = 0;
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	while (i < nb_of_philo)
	{
		pthread_join(philosophers[i].thread, NULL);
		++i;
	}
}

static void	run_simulation(t_philosopher *philosophers, t_fork *forks)
{
	pthread_t	philo_watcher_thread;
	bool		*health_check;
	bool		*waiting_for_threads;
	unsigned long long nb_of_philo;
	unsigned long long	i;

	output_status(NULL, NULL);
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	health_check = malloc(sizeof (*health_check));
	waiting_for_threads = malloc(sizeof (*waiting_for_threads));
	*health_check = true;
	*waiting_for_threads = true;
	i = 0;
	while (i < nb_of_philo)
	{
		philosophers[i].forks = forks;
		philosophers[i].health_check = health_check;
		philosophers[i].waiting_for_threads = waiting_for_threads;
		++i;
	}
	i = 0;
	while (i < nb_of_philo)
	{
		pthread_create(&philosophers[i].thread, NULL, (void *)(void *)&spawn_philosopher, &philosophers[i]);
		i += 1;
	}
	i = 1;
	while (i < nb_of_philo)
	{
		pthread_create(&philosophers[i].thread, NULL, (void *)(void *)&spawn_philosopher, &philosophers[i]);
		i += 2;
	}
	pthread_create(&philo_watcher_thread, NULL, (void *)(void *)&philo_watcher, philosophers);
	pthread_join(philo_watcher_thread, NULL);
	terminate_philo_threads(philosophers);
}

static void	destroy_mutexes(void)
{
	size_t			i;
	pthread_mutex_t	*mutexes;

	i = 0;
	mutexes = get_mutexes();
	while (i < PHILO_ONE_TOTAL_MUTEX)
		pthread_mutex_destroy(&mutexes[i++]);
}

static void	init_mutexes(void)
{
	size_t			i;
	pthread_mutex_t	*mutexes;

	i = 0;
	mutexes = get_mutexes();
	while (i < PHILO_ONE_TOTAL_MUTEX)
		pthread_mutex_init(&mutexes[i++], NULL);
}

int	main(int ac, char **av)
{
	t_philosopher		*philosophers;
	t_fork				*forks;
	
	if (!parse_params(ac, av))
		return (1);
	philosophers = get_philosophers();
	if (philosophers == NULL)
		return (1);
	forks = forks_init();
	if (forks == NULL)
		return (1);
	init_mutexes();
	run_simulation(philosophers, forks);
	free(philosophers);
	free(forks);
	destroy_mutexes();
	return (0);
}
