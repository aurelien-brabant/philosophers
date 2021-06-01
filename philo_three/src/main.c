#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#include "philo_three.h"
#include "philo_error.h"

static void	kill_processes(t_philosopher *philosophers)
{
	unsigned long long	nb_of_philo;
	unsigned long long	i;

	i = 0;
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	while (i < nb_of_philo)
		kill(philosophers[i++].pid, SIGKILL);
}

void	run_simulation(t_philosopher *philosophers)
{
	unsigned long long	i;
	unsigned long long	nb_of_philo;
	int					pid;
	int					status;

	i = 0;
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	output_status(NULL, NULL);
	get_timestamp();
	while (i < nb_of_philo)
	{
		pid = fork();
		if (pid == 0)
			spawn_philosopher(&philosophers[i]);
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
		return (philo_error_print(ERROR_ARGS_PARSING));
	if (!semaphores_init())
		return (philo_error_print(ERROR_SEM_INIT));
	philosophers = philosophers_init();
	if (philosophers == NULL)
	{	
		semaphores_close();
		semaphores_unlink();
		return (philo_error_print(ERROR_PHILOSOPHERS_INIT));
	}
	run_simulation(philosophers);
	destroy_philo_three(philosophers);
	return (EXIT_SUCCESS);
}
