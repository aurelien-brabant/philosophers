#include <stdlib.h>

#include "philo_three.h"
#include "philo_error.h"

/*
** Initialize output buffer and timestamp, that will be copied by each forked
** process.
*/

void	run_simulation(t_philosopher *philosophers)
{
	output_status(NULL, NULL);
	get_timestamp();
	process_start_children(philosophers);
	process_wait_for_children(philosophers);
}

int	main(int ac, char **av)
{
	t_philosopher		*philosophers;

	if (!parse_params(ac, av))
		return (philo_error_print(ERROR_ARGS_PARSING));
	if (!semaphores_init())
		return (philo_error_print(ERROR_SEM_INIT));
	philosophers = philosophers_init();
	if (philosophers == NULL)
	{	
		semaphores_close();
		semaphores_unlink();
		return (philo_error_print(ERROR_PHILOSOPHERS_INIT));
	}
	run_simulation(philosophers);
	destroy_philo_three(philosophers);
	return (EXIT_SUCCESS);
}
