#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "philo_bonus.h"

/*
** Kill all child processes. A pid of 0 means that for some reason the pid
** could not be obtained when calls to fork have been issued. This means
** that the call to fork returned -1, which means an error occured.
*/

void	process_kill_children(t_philosopher *philosophers)
{
	unsigned int	i;

	i = 0;
	while (i < philosophers[0].params[NB_PHILO])
	{
		if (philosophers[i].pid != 0)
			kill(philosophers[i].pid, SIGKILL);
		++i;
	}
}

/*
** Start child processes, each one representing a philosopher.
*/

void	process_start_children(t_philosopher *philosophers)
{
	unsigned int	i;
	int				pid;

	i = 0;
	while (i < philosophers[0].params[NB_PHILO])
	{
		pid = fork();
		if (pid == -1)
		{
			philo_error_print(ERROR_FORK);
			return ;
		}
		if (pid == 0)
			spawn_philosopher(&philosophers[i]);
		else
			philosophers[i++].pid = pid;
	}
}

void	process_wait_for_children(t_philosopher *philosophers)
{
	int					status;
	unsigned long long	i;

	i = 0;
	while (waitpid(-1, &status, 0) != -1 && status == 0)
		++i;
	if (i < philosophers[0].params[NB_PHILO])
		process_kill_children(philosophers);
}
