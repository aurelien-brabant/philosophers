#include "philo.h"

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
	unsigned long long	i;

	i = 0;
	while (i < philosophers[0].params[NUMBER_OF_PHILOSOPHERS])
		pthread_join(philosophers[i++].thread, NULL);
}

int	thread_philo_start_even(t_philosopher *philosophers)
{
	unsigned long long	i;
	int					pthread_create_ret;

	i = 0;
	while (i < philosophers[0].params[NUMBER_OF_PHILOSOPHERS])
	{
		pthread_create_ret = pthread_create(&philosophers[i].thread, NULL,
				(void *)(void *)&spawn_philosopher, &philosophers[i]);
		if (pthread_create_ret != 0)
		{
			philo_error_print(ERROR_THREAD_CREATE);
			return (pthread_create_ret);
		}
		i += 2;
	}
	return (0);
}

int	thread_philo_start_odd(t_philosopher *philosophers)
{
	unsigned int	i;
	int				pthread_create_ret;

	i = 1;
	while (i < philosophers[0].params[NUMBER_OF_PHILOSOPHERS])
	{
		pthread_create_ret = pthread_create(&philosophers[i].thread, NULL,
				(void *)(void *)&spawn_philosopher, &philosophers[i]);
		if (pthread_create_ret != 0)
		{
			philo_error_print(ERROR_THREAD_CREATE);
			return (pthread_create_ret);
		}
		i += 2;
	}
	return (0);
}
