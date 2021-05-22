#include <stdlib.h>

#include "philo_one.h"
#include "lib.h"

int	main(int ac, char **av)
{
	unsigned long long	params[PHILO_PARAM_MAX];
	t_philosopher		*philo;

	if (!parse_params(ac, av, params))
		return (1);
	philo = dress_philosophy_table(params);
	if (philo == NULL)
		return (1);
	destroy_philosophers(philo->left_philo);
	return (0);
}
