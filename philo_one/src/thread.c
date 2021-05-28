#include "philo_one.h"

/*
** Attempt to join all the threads, each one being a philosopher
** thread_terminate_simulation needs to be called after the philo_watcher
** thread has terminated, which means that a philosopher is dead OR that
** each philosopher ate the required amount of times.
**
** By joining each thread in a loop, we can ensure that all the philosophers
** are stopped properly, and that ressources are safely freed.
** As the program is going to terminate right after that, this does not really
** matter though.
*/

void	thread_terminate_simulation(t_philosopher *philosophers)
{
	unsigned long long nb_of_philo;
	unsigned long long i;

	i = 0;
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	while (i < nb_of_philo)
		pthread_join(philosophers[i++].thread, NULL);
}

/*
** Start all philosophers which's id is odd or even in a single call.
** This allows better synchronization in philo_one.
** The start_even_first boolean determines if only even philosophers are going
** to be started. If it is set to false, then only odd philosophers will be
** started.
*/

int	thread_philo_start_parity(t_philosopher *philosophers, bool start_even_first)
{
	unsigned long long i;
	unsigned long long	nb_of_philo;
	int					pthread_create_ret;

	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	i = start_even_first;
	while (i < nb_of_philo)
	{
		pthread_create_ret = pthread_create(&philosophers[i].thread, NULL,
			(void *)(void *)&spawn_philosopher, &philosophers[i]);
		if (pthread_create_ret != 0)
			return (pthread_create_ret);
		i += 2;
	}
	return (0);
}
