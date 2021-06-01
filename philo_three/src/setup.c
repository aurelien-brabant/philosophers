#include <stdlib.h>
#include <unistd.h>

#include "philo_three.h"
#include "philo_error.h"

/*
** Free all the allocated memory for philo_three.
** Can be used if an error occured to free what can be free,
** or at the end of the simulation if everything went well.
*/

void	destroy_philo_three(t_philosopher *philosophers)
{
	if (semaphores_close() != PHILO_THREE_SEM_MAX)
		philo_error_print(ERROR_SEM_CLOSE);
	if (semaphores_unlink() != PHILO_THREE_SEM_MAX)
		philo_error_print(ERROR_SEM_UNLINK);
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
		philosophers[i].pid = 0;
		++i;
	}
	return (philosophers);
}
