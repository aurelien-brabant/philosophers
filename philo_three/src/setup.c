#include <stdlib.h>
#include <unistd.h>

#include "philo_three.h"

/*
** Free all the allocated memory for philo_one.
** Can be used if an error occured to free what can be free,
** or at the end of the simulation if everything went well.
*/

void	destroy_philo_three(t_philosopher *philosophers)
{
	if (semaphores_close() != PHILO_THREE_SEM_MAX)
		dputs("Semaphores could not be closed properly\n", STDERR_FILENO);
	if (semaphores_unlink() != PHILO_THREE_SEM_MAX)
		dputs("Semaphores could not be unlinked properly\n", STDERR_FILENO);
	free(philosophers);
}

t_philosopher	*philosophers_init(void)
{
	t_philosopher		*philosophers;
	unsigned long long	*params;
	unsigned long long	nb_of_philo;
	unsigned long long	i;

	params = get_params();
	nb_of_philo = params[NUMBER_OF_PHILOSOPHERS];
	philosophers = malloc(sizeof (*philosophers) * nb_of_philo);
	if (philosophers == NULL)
		return (NULL);
	i = 0;
	while (i < nb_of_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].last_meal_timestamp = 0;
		philosophers[i].state = PHILO_STATE_THINKING; 
		philosophers[i].eat_count = 0;
		philosophers[i].philosophers = philosophers;
		++i;
	}
	return (philosophers);
}
