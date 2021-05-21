#include "philo/core.h"
#include "philo/lib.h"
#include "philo/types.h"

int	main(int ac, char **av)
{
	t_philo	philo;
	t_philo_param	param_id;

	param_id = NUMBER_OF_PHILOSOPHERS;
	--ac;
	++av;
	if (ac < PHILO_PARAM_MAX - 1)
		return (error_out("Parsing: too few arguments supplied", 1));
	if (ac > PHILO_PARAM_MAX)
		return (error_out("Parsing: too much arguments supplied", 1));
	while (param_id < PHILO_PARAM_MAX && ac > (int)param_id)
	{
		if (!parse_uint(av[param_id], &philo.params[param_id]))
			return (error_out("Error during parsing of command line arguments", 1));
		++param_id;
	}
	return (0);
}
