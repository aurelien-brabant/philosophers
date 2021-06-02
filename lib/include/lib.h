#ifndef LIB_H
# define LIB_H
# include <stddef.h>
# include <stdbool.h>

/* 
** These two enums are usable in the exact same way no matter the version
** of philosopher 
*/

typedef enum e_philo_param
{
	NUMBER_OF_PHILOSOPHERS = 0,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT,
	PHILO_PARAM_MAX
}	t_philo_param;

typedef enum e_philo_state
{
	PHILO_STATE_DEAD = 0,
	PHILO_STATE_SLEEPING,
	PHILO_STATE_EATING,
	PHILO_STATE_THINKING,
}	t_philo_state;

typedef unsigned long long int	t_timestamp;

size_t				ft_strlen(const char *s);
int					dputs(const char *s, int fd);
bool				parse_params(int ac, char **av);
t_timestamp			get_timestamp(void);
unsigned long long	*get_params(void);
void				ft_msleep(unsigned long long ms);
const char			*get_state_string(t_philo_state state);
bool				parse_uint(const char *sint, unsigned long long *n);

#endif
