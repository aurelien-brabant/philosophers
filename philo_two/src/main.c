#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "philo_two.h"
#include "philo_error.h"

/*
** Wait for each thread, which is a philosopher, to terminate properly
** before moving on.
*/

static void	run_simulation(t_philosopher *philosophers)
{
	pthread_t			philo_watcher_thread;
	bool				*health_check;
	unsigned long long	nb_of_philo;
	unsigned long long	i;

	output_status(NULL, NULL);
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	health_check = malloc(sizeof (*health_check));
	if (health_check == NULL)
		return ;
	*health_check = true;
	i = 0;
	while (i < nb_of_philo)
		philosophers[i++].health_check = health_check;
	if (thread_philo_start_range(philosophers, 0, nb_of_philo / 2) != 0)
		return ;
	usleep(100);
	if (thread_philo_start_range(philosophers,
			nb_of_philo / 2, nb_of_philo) != 0)
		return ;
	if (pthread_create(&philo_watcher_thread, NULL,
			(void *)(void *) &philo_watcher, philosophers) != 0)
		philo_error_print(ERROR_THREAD_CREATE);
	else
		pthread_join(philo_watcher_thread, NULL);
}

int	main(int ac, char **av)
{
	t_philosopher	*philosophers;

	if (!parse_params(ac, av))
		return (philo_error_print(ERROR_ARGS_PARSING));
	if (!semaphores_init())
		return (philo_error_print(ERROR_SEM_INIT));
	philosophers = philosophers_init();
	if (philosophers == NULL)
		return (ERROR_PHILOSOPHERS_INIT);
	run_simulation(philosophers);
	thread_terminate_simulation(philosophers);
	destroy_philo_two(philosophers);
	return (0);
}
