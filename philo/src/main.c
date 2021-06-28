#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "philo.h"

static void	run_simulation(t_philosopher *philosophers)
{
	pthread_t			philo_watcher_thread;

	output_status(NULL, NULL);
	if (thread_philo_start_odd(philosophers) != 0)
		return ;
	usleep(1000);
	if (thread_philo_start_even(philosophers) != 0)
		return ;
	if (pthread_create(&philo_watcher_thread, NULL,
			(void *)(void *)&philo_watcher, philosophers) != 0)
		philo_error_print(ERROR_THREAD_CREATE);
	else
		pthread_join(philo_watcher_thread, NULL);
}

static int	prepare_simulation(t_philosopher *philosophers)
{
	unsigned int	i;
	bool			*health_check;
	pthread_mutex_t	*out_mutex;

	out_mutex = malloc(sizeof (*out_mutex));
	if (out_mutex == NULL)
		return (1);
	if (pthread_mutex_init(out_mutex, 0) != 0)
		return (philo_error_print(ERROR_MUTEX_INIT));
	health_check = malloc(sizeof (*health_check));
	if (health_check == NULL)
		return (2);
	*health_check = true;
	i = 0;
	while (i < philosophers[0].params[NUMBER_OF_PHILOSOPHERS])
	{
		philosophers[i].health_check = health_check;
		philosophers[i].out_mutex = out_mutex;
		++i;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philosopher		*philosophers;
	static unsigned int	params[PHILO_PARAM_MAX];

	if (!parse_params(ac, av, params))
		return (philo_error_print(ERROR_ARGS_PARSING));
	philosophers = philosophers_init(params);
	if (philosophers == NULL)
		return (philo_error_print(ERROR_PHILOSOPHERS_INIT));
	if (prepare_simulation(philosophers) != 0)
		return (1);
	run_simulation(philosophers);
	thread_terminate_simulation(philosophers);
	destroy_simulation(philosophers);
	return (0);
}
