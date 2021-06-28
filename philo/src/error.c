#include <unistd.h>
#include <stdlib.h>

#include "lib.h"
#include "philo_error.h"

static const char	*g_errors[] = {
	"Could not parse command line arguments\nUsage: ./philo_one <nb_of_philo> "
	"<time_to_die> <time_to_eat> <time_to_sleep>"
	" [number_of_times_each_philo_must_eat]",
	"Could not initialize mutex properly",
	"Could not destroy mutex properly",
	"Could not initialize philosophers",
	"Thread could not created",
	"Thread could not be detached properly",
	"Thread could not be joined",
};

static const char	*g_error_prefix = "\033[1;31mError: \033[0m";

int	philo_error_print(t_philo_error philo_error)
{
	write(STDERR_FILENO, g_error_prefix, ft_strlen(g_error_prefix));
	write(STDERR_FILENO, g_errors[philo_error],
		ft_strlen(g_errors[philo_error]));
	write(STDERR_FILENO, "\n", 1);
	return (philo_error + 1);
}