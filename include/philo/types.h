#ifndef TYPES_H
# define TYPES_H

typedef enum e_philo_param
{
	NUMBER_OF_PHILOSOPHERS = 0,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT,
	PHILO_PARAM_MAX
}	t_philo_param;

typedef struct s_philo
{
	unsigned long long	params[PHILO_PARAM_MAX];
}	t_philo;

#endif
