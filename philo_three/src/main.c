#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "philo_three.h"

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
	while (i < nb_of_philo)
	{
		philosophers[i].semaphores = get_semaphores();
		pid = fork();
		if (pid == 0)
		{
			spawn_philosopher(&philosophers[i]);
			exit(0);
		}
		else 
			philosophers[i].pid = pid;
		++i;
	}
	/* waitpid until a philosopher dies */
	i = 0;
	while (1);
	while (waitpid(-1, &status, 0) != -1 && status == 0)
		++i;
	if (i == nb_of_philo)
		printf("Philosophers have eaten as expected.\n");
	else
		printf("A philosopher died somehow :(\n");
}

static void	kill_processes(t_philosopher *philosophers)
{
	unsigned long long	nb_of_philo;
	unsigned long long	i;

	i = 0;
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	while (i < nb_of_philo)
		kill(philosophers[i++].pid, SIGINT);
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
