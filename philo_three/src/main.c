#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "philo_three.h"

static void	kill_processes(t_philosopher *philosophers)
{
	unsigned long long	nb_of_philo;
	unsigned long long	i;

	i = 0;
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	while (i < nb_of_philo)
		kill(philosophers[i++].pid, SIGKILL);
}

/*
** Wait for each thread, which is a philosopher, to terminate properly
** before moving on.
*/

void	run_simulation(t_philosopher *philosophers)
{
	unsigned long long	i;
	unsigned long long	nb_of_philo;
	int					pid;
	int					status;

	i = 0;
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	get_timestamp();
	output_status(NULL, NULL);
	while (i < nb_of_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			philosophers[i].philosophers = philosophers;
			spawn_philosopher(&philosophers[i]);
		}
		else 
			philosophers[i].pid = pid;
		++i;
	}
	i = 0;
	while (waitpid(-1, &status, 0) != -1 && status == 0)
		++i;
	if (i < nb_of_philo)
		kill_processes(philosophers);
}

int	main(int ac, char **av)
{
	t_philosopher		*philosophers;
	
	if (!parse_params(ac, av))
		return (1);
	if (!semaphores_init())
		return (1);
	philosophers = philosophers_init();
	if (philosophers == NULL)
		return (1);
	run_simulation(philosophers);
	semaphores_destroy();
	kill_processes(philosophers);
	destroy_philo_two(philosophers);
	return (0);
}
