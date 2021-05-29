#include <stdlib.h>

#include "philo_two.h"

/*
** Free all the allocated memory for philo_one.
** Can be used if an error occured to free what can be free,
** or at the end of the simulation if everything went well.
*/

void	destroy_philo_one(t_philosopher *philosophers)
{
	free(philosophers[0].health_check);
	free(philosophers);
}

t_philosopher	*philosophers_init(void)
{
	t_philosopher	*philosophers;
	unsigned long long	nb_of_philo;
	unsigned long long	i;

	nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
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
		++i;
	}
	return (philosophers);
}
