#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "philo_three.h"
#include "errno.h"

sem_t	**get_semaphores(void)
{
	static sem_t	*semaphores[PHILO_TWO_SEMAPHORE_MAX];

	return (semaphores);
}

/*
** Create the semaphores, unlinking them if they were already existing.
*/

bool	semaphores_init(unsigned long long nb_of_philo)
{
	sem_t	*sem_fork;
	sem_t	*sem_state;
	bool	is_successful;

	sem_unlink(SEM_NM_FORK);
	sem_unlink(SEM_NM_STATE);
	sem_fork = sem_open(SEM_NM_FORK, O_CREAT, 0644, nb_of_philo);
	sem_state = sem_open(SEM_NM_STATE, O_CREAT, 0644, 1);
	is_successful = sem_fork && sem_state;
	if (!is_successful)
		dputs("Could not create semaphores properly!\n", STDERR_FILENO);
	if (sem_fork != SEM_FAILED)
		sem_close(sem_fork);
	if (sem_state != SEM_FAILED)
		sem_close(sem_state);
	return (is_successful);
}

void	semaphores_destroy(void)
{
	sem_t	**semaphores;

	semaphores = get_semaphores();
	sem_close(semaphores[PHILO_TWO_STATE_SEMAPHORE]);
	sem_close(semaphores[PHILO_TWO_FORK_SEMAPHORE]);
	sem_unlink("/fork");
	sem_unlink("/state");
}
