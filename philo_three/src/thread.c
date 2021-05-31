#include <unistd.h>

#include "philo_three.h"

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

int	thread_philo_start_range(t_philosopher *philosophers, unsigned long long low, unsigned long long high)
{
	int					pthread_create_ret;

	while (low < high)
	{
		pthread_create_ret = pthread_create(&philosophers[low].thread, NULL,
			(void *)(void *)&spawn_philosopher, &philosophers[low]);
		if (pthread_create_ret != 0)
			return (pthread_create_ret);
		++low;
	}
	return (0);
}