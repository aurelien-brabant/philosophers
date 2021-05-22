#ifndef LIB_H
# define LIB_H
# include <stddef.h>
# include <stdbool.h>

typedef enum e_philo_param
{
	NUMBER_OF_PHILOSOPHERS = 0,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT,
	PHILO_PARAM_MAX
}	t_philo_param;

size_t	ft_strlen(const char *s);
bool	parse_uint(const char *s, unsigned long long *n);
int		dputs(const char *s, int fd);
int		error_out(const char *msg, int exit_code);
bool	parse_params(int ac, char **av, unsigned long long *params);

#endif
