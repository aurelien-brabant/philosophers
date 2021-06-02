#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include "philo_two.h"

/*
** Get an array which contains the addresses of all the sem_t objects used
** to interface with semaphores.
*/

sem_t	**get_semaphores(void)
{
	static sem_t	*semaphores[PHILO_TWO_SEM_MAX];

	return (semaphores);
}

/*
** Unlink semaphores, removing them from the system.
**
** The number of successfully unlinked semaphores is returned.
** If this number is different than PHILO_TWO_SEM_MAX, it means that at least
** one semaphore could not be unlinked properly.
*/

size_t	semaphores_unlink(void)
{
	size_t	unlinked;

	unlinked = 0;
	unlinked += (sem_unlink(SEM_NM_FORK) == 0);
	unlinked += (sem_unlink(SEM_NM_STATE) == 0);
	return (unlinked);
}

/*
** close semaphores stored by get_semaphores.
**
** The number of successfully closed semaphores is returned. This number
** should be equal to PHILO_TWO_SEM_MAX if all the semaphores have been
** closed without error.
**
** /!\ For unknown reasons, any call to sem_close *CAN* produce an infinite loop
** on MacOS. It appears that posting the semaphore before the call can solve
** the issue, but that's definitely not something we can do if we want the output
** to be definitely locked after the death of a philosopher.
*/

size_t	semaphores_close(void)
{
	unsigned long long	i;
	sem_t				**semaphores;
	size_t				closed;	

	i = 0;
	closed = 0;
	semaphores = get_semaphores();
	while (i < PHILO_TWO_SEM_MAX)
		closed += (sem_close(semaphores[i++]) != -1);
	return (closed);
}

/*
** Initialize semaphores, that will be widely available using get_semaphores.
**
** A boolean value is returned: it indicates whether or not the initialization
** went well.
**
** NOTE: semaphores are unlinked even if they don't exist in order to ensure that
** old ones will not be reused.
*/

bool	semaphores_init(void)
{
	sem_t	**sems;

	sems = get_semaphores();
	semaphores_unlink();
	sems[PHILO_TWO_SEM_FORK] = sem_open(SEM_NM_FORK, O_CREAT, 0644,
			get_params()[NUMBER_OF_PHILOSOPHERS]);
	sems[PHILO_TWO_SEM_STATE] = sem_open(SEM_NM_STATE, O_CREAT, 0644, 1);
	return (sems[PHILO_TWO_SEM_FORK] != SEM_FAILED
		&& sems[PHILO_TWO_SEM_STATE] != SEM_FAILED);
}
