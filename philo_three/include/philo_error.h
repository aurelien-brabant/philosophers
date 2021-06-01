#ifndef PHILO_ERROR_H
# define PHILO_ERROR_H

typedef enum	e_philo_error
{
	ERROR_ARGS_PARSING = 0,
	ERROR_SEM_INIT,
	ERROR_SEM_CLOSE,
	ERROR_SEM_UNLINK,
	ERROR_SEM_POST,
	ERROR_SEM_WAIT,
	ERROR_PHILOSOPHERS_INIT,
	ERROR_THREAD_CREATE,
	ERROR_THREAD_DETACH,
	ERROR_THREAD_JOIN,
	
}	t_philo_error;

int	philo_error_print(t_philo_error philo_error);

#endif
