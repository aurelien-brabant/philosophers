#include "philo_one.h"
#include "philo_error.h"

/*
** Destroy global mutexes, freeing all the memory allocated for it.
**
** The number of successfully destroyed mutexes is returned, which should be
** equal to PHILO_ONE
*/

size_t	destroy_mutexes(void)
{
	size_t			i;
	size_t			destroyed;
	pthread_mutex_t	*mutexes;

	i = 0;
	destroyed = 0;
	mutexes = get_mutexes();
	while (i < PHILO_ONE_TOTAL_MUTEX)
		destroyed += (pthread_mutex_destroy(&mutexes[i++]) == 0);
	return (destroyed);
}

/*
** Initialize global mutexes.
*/

bool	init_mutexes(void)
{
	int				i;
	pthread_mutex_t	*mutexes;

	i = 0;
	mutexes = get_mutexes();
	while (i < PHILO_ONE_TOTAL_MUTEX)
	{
		if (pthread_mutex_init(&mutexes[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&mutexes[i]);
			return (false);
		}
		++i;
	}
	return (true);
}

/*
** Get global mutexes from anywhere. 
*/

pthread_mutex_t	*get_mutexes(void)
{
	static pthread_mutex_t	mutexes[PHILO_ONE_TOTAL_MUTEX];

	return (mutexes);
}
