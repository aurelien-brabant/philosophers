#include <unistd.h>
#include <sys/wait.h>

#include "philo_three.h"

static void	*start_philosopher()
{
	if ()
}

void	start_philosophers_as_child_processes(t_philosopher *philosophers)
{
	unsigned long long	i;
	unsigned long long	nb_of_philo;

	i = 0;
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	while (i < nb_of_philo)
	{
		if (fork() == 0)
		{
			spawn_philosopher(&philosophers[i]);
			break ;
		}
	}
}
