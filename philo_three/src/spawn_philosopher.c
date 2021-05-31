#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "philo_three.h"
#include "lib.h"

static bool	open_semaphores(sem_t **state_sem_loc, sem_t **fork_sem_loc)
{
	*fork_sem_loc = sem_open(SEM_NM_FORK, 0);
	if (*fork_sem_loc == SEM_FAILED)
	{
		dputs("fork sem could not be opened by child process\n", STDERR_FILENO);
		return (false);
	}
	*state_sem_loc = sem_open(SEM_NM_STATE, 0);
	if (*state_sem_loc == SEM_FAILED)
	{
		dputs("state sem could not be opened by child process\n", STDERR_FILENO);
		sem_close(*fork_sem_loc);
		return (false);
	}
	return (true);
}

/*
** Spawn a philosopher, making him live until he spends time_to_die ms without
** eating.
**
** If there's only one philosopher and therefore only one fork available, then
** the philosopher is not going to take any fork and will just die at
** time_to_die ms.
*/

void	spawn_philosopher(t_philosopher *philo)
{
	unsigned long long	philo_nb;
	sem_t				*fork_sem;
	sem_t				*state_sem;

	if (!open_semaphores(&state_sem, &fork_sem))
		exit(1);
	philo_nb = get_params()[NUMBER_OF_PHILOSOPHERS];
	while (1)
	{
		philo_routine_eat(philo, state_sem, fork_sem);
		philo_routine_sleep(philo, state_sem);
		philo_routine_think(philo, state_sem);
		usleep(100);
		printf("Spawned philo %lld\n", philo->id);
	}
	exit(0);
}
