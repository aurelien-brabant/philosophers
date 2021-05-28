#include <limits.h>

#include "lib.h"

/*
** Parse the command line parameters, filling params accordingly.
** If any error occurs, a descriptive message is outputed on STDERR.
**
** @return true if command line has been parsed without any error, false
** otherwise.
*/

bool	parse_params(int ac, char **av)
{
	t_philo_param		param_id;
	unsigned long long	*params;

	params = get_params();
	param_id = NUMBER_OF_PHILOSOPHERS;
	--ac;
	++av;
	if (ac < PHILO_PARAM_MAX - 1)
		return (error_out("Parsing: too few arguments supplied", false));
	if (ac > PHILO_PARAM_MAX)
		return (error_out("Parsing: too much arguments supplied", false));
	while (param_id < PHILO_PARAM_MAX && ac > (int)param_id)
	{
		if (!parse_uint(av[param_id], &params[param_id]))
			return (error_out("Error during parsing of command line arguments", false));
		++param_id;
	}
	if (ac < 5)
		params[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT] = ULLONG_MAX;
	return (true);
}
