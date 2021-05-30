#include "philo_two.h"

/*
** Destroy global mutexes, freeing all the memory allocated for it.
*/

void	destroy_mutexes(void)
{
	size_t			i;
	pthread_mutex_t	*mutexes;

	i = 0;
	mutexes = get_mutexes();
	while (i < PHILO_ONE_TOTAL_MUTEX)
		pthread_mutex_destroy(&mutexes[i++]);
}

/*
** Initialize global mutexes.
*/

void	init_mutexes(void)
{
	size_t			i;
	pthread_mutex_t	*mutexes;

	i = 0;
	mutexes = get_mutexes();
	while (i < PHILO_ONE_TOTAL_MUTEX)
		pthread_mutex_init(&mutexes[i++], NULL);
}

/*
** Get global mutexes from anywhere. 
*/

pthread_mutex_t *get_mutexes(void)
{
    static pthread_mutex_t  mutexes[PHILO_ONE_TOTAL_MUTEX];

    return (mutexes);
}
