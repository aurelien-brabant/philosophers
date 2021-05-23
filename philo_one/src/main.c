#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "philo_one.h"
#include "lib.h"

bool	are_all_philosophers_alive(t_philosopher *philo)
{
	while (1)
	{
		if (philo->state == PHILO_STATE_DEAD)
			return (false);
		if (philo->id == philo->params[NUMBER_OF_PHILOSOPHERS])
			break ;
		philo = philo->right_philo;
	}
	return (true);
}

static void	run_simulation(t_philosopher *philo)
{
	size_t	i;
	pthread_t	philo_watcher_thread;
	bool		*health_check;

	i = 0;
	health_check = malloc(sizeof (*health_check));
	*health_check = true;
	pthread_create(&philo_watcher_thread, NULL, (void *)(void *)&philo_watcher, health_check);
	while (i < philo->params[NUMBER_OF_PHILOSOPHERS])
	{
		philo->state = PHILO_STATE_THINKING;
		philo->health_check = health_check;
		pthread_create(&philo->thread, NULL, (void *)(void *)&spawn_philosopher, philo);
		pthread_detach(philo->thread);
		philo = philo->right_philo;
		++i;
	}
	pthread_join(philo_watcher_thread, NULL);
}

static void	destroy_mutexes(pthread_mutex_t *mutexes)
{
	size_t	i;

	i = 0;
	while (i < PHILO_ONE_TOTAL_MUTEX)
		pthread_mutex_destroy(&mutexes[i++]);
}

int	main(int ac, char **av)
{
	unsigned long long	params[PHILO_PARAM_MAX];
	pthread_mutex_t		mutexes[PHILO_ONE_TOTAL_MUTEX];
	t_philosopher		*philo;
	
	if (!parse_params(ac, av, params))
		return (1);
	pthread_mutex_init(&mutexes[PHILO_ONE_PRINTF_MUTEX], NULL);
	philo = dress_philosophy_table(params, mutexes);
	if (philo == NULL)
		return (1);
	run_simulation(philo);
	destroy_philosophers(philo->left_philo);
	destroy_mutexes(mutexes);
	return (0);
}
