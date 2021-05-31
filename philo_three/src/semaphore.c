#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "philo_three.h"
#include "errno.h"

sem_t	**get_semaphores(void)
{
	static sem_t	*semaphores[PHILO_THREE_SEM_MAX];

	return (semaphores);
}

/*
** Initialize semaphores, that will be widely available using get_semaphores.
*/

bool	semaphores_init(void)
{
	sem_t	**sems;

	sems = get_semaphores();
	sem_unlink(SEM_NM_FORK);
	sem_unlink(SEM_NM_STATE);
	sems[PHILO_THREE_SEM_FORK] = sem_open(SEM_NM_FORK, O_CREAT, 0644, get_params()[NUMBER_OF_PHILOSOPHERS]);
	sems[PHILO_THREE_SEM_STATE] = sem_open(SEM_NM_STATE, O_CREAT, 0644, 1);
	if (sems[PHILO_THREE_SEM_FORK] == SEM_FAILED 
		|| sems[PHILO_THREE_SEM_STATE] == SEM_FAILED)
	{
		dputs("Error: could not initialize semaphores!\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

void	semaphores_destroy(void)
{
	sem_t	**semaphores;

	semaphores = get_semaphores();
	sem_close(semaphores[PHILO_THREE_SEM_FORK]);
	sem_close(semaphores[PHILO_THREE_SEM_STATE]);
	sem_unlink(SEM_NM_FORK);
	sem_unlink(SEM_NM_STATE);
}
