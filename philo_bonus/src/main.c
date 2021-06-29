#include <stdlib.h>
#include <semaphore.h>
#include <sys/errno.h>
#include <fcntl.h>

#include "philo_bonus.h"

/*
** Initialize output buffer and timestamp, that will be copied by each forked
** process.
** Timestamp NEEDS to be initialized here before any forking is done, otherwise
** timestamp will not be global and simulation will be truncated.
*/

static void	run_simulation(t_philosopher *philosophers)
{
	output_status(NULL, NULL);
	get_timestamp();
	process_start_children(philosophers);
	process_wait_for_children(philosophers);
}

/*
** Exit the master process with the specified exit status, and free the
** dynamically allocated ressources. The semaphores are also unlinked, to
** avoid letting them live in the system.
*/

static void	exit_clean(t_philosopher *philosophers, int status)
{
	free(philosophers);
	if (sem_unlink(SEM_NM_STATE) != 0 || sem_unlink(SEM_NM_FORK) != 0)
		philo_error_print(ERROR_SEM_UNLINK);
	exit(status);
}

static int	semaphore_init(unsigned int nb_philo)
{
	sem_t			*sem_state;
	sem_t			*sem_fork;

	sem_unlink(SEM_NM_FORK);
	sem_unlink(SEM_NM_STATE);
	sem_state = sem_open(SEM_NM_STATE, O_CREAT, 0664, 1);
	sem_fork = sem_open(SEM_NM_FORK, O_CREAT, 0664, nb_philo);
	if (sem_state == SEM_FAILED || sem_fork == SEM_FAILED)
		return (ERROR_SEM_OPEN);
	if (sem_close(sem_fork) != 0 || sem_close(sem_state) != 0)
		return (ERROR_SEM_CLOSE);
	return (0);
}

static t_philosopher	*philosophers_init(unsigned int *params)
{
	t_philosopher		*philosophers;
	unsigned int		i;

	philosophers = malloc(sizeof (*philosophers) * params[NB_PHILO]);
	if (philosophers == NULL)
		return (NULL);
	i = 0;
	while (i < params[NB_PHILO])
	{
		philosophers[i].id = i + 1;
		philosophers[i].params = params;
		philosophers[i].last_meal_ts = 0;
		philosophers[i].state = PHILO_STATE_THINKING;
		philosophers[i].eat_count = 0;
		philosophers[i].philosophers = philosophers;
		philosophers[i].pid = 0;
		++i;
	}
	return (philosophers);
}

int	main(int ac, char **av)
{
	t_philosopher	*philosophers;
	unsigned int	params[PHILO_PARAM_MAX];
	int				ret;

	if (parse_params(ac, av, params) != 0)
		return (philo_error_print(ERROR_ARGS_PARSING));
	philosophers = philosophers_init(params);
	if (philosophers == NULL)
		return (philo_error_print(ERROR_PHILOSOPHERS_INIT));
	ret = semaphore_init(params[NB_PHILO]);
	if (ret != 0)
		exit_clean(philosophers, philo_error_print(ret));
	run_simulation(philosophers);
	free(philosophers);
	return (EXIT_SUCCESS);
}
