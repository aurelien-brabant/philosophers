#include <semaphore.h>

#include "philo_error.h"

void	ft_sem_post(sem_t *sem)
{
	if (sem_post(sem) == -1)
		philo_error_print(ERROR_SEM_POST);
}

void	ft_sem_wait(sem_t *sem)
{
	if (sem_wait(sem) == -1)
		philo_error_print(ERROR_SEM_WAIT);
}
