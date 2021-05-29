#include <semaphore.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include "philo_two.h"
#include "errno.h"

sem_t	**get_semaphores(void)
{
	static sem_t	*semaphores[PHILO_TWO_SEMAPHORE_MAX];

	return (semaphores);
}

bool	semaphores_init(void)
{
	sem_t				**semaphores;
	unsigned long long	i;
	unsigned long long	nb_of_philo;

	semaphores = get_semaphores();
	semaphores[PHILO_TWO_STATE_SEMAPHORE] = sem_open("/state", O_CREAT, 0777, 1);
	if (semaphores[PHILO_TWO_STATE_SEMAPHORE] == SEM_FAILED)
	{
		printf("%s\n", strerror(errno));
	}
	semaphores[PHILO_TWO_FORK_SEMAPHORE] = sem_open("/fork", O_CREAT, 0777, 1);
	if (semaphores[PHILO_TWO_FORK_SEMAPHORE] == SEM_FAILED)
		return (false);
	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
	i = 0;
	while (i < nb_of_philo)
	{
		if (sem_post(semaphores[PHILO_TWO_FORK_SEMAPHORE]) == -1)
			return (false);
		++i;
	}
	return (true);
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
