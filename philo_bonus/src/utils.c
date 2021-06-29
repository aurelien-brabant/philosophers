#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include "philo_bonus.h"

const char	*get_state_string(t_philo_state state)
{
	static const char	*s[] = {
		[PHILO_STATE_DEAD] = " \033[1;31mdied\033[0m\n",
		[PHILO_STATE_EATING] = " is eating\n",
		[PHILO_STATE_SLEEPING] = " is sleeping\n",
		[PHILO_STATE_THINKING] = " is thinking\n"
	};

	return (s[state]);
}

int	parse_uint(const char *sint, unsigned int *n)
{
	unsigned int	new_val;

	*n = 0;
	if (*sint == '\0')
		return (1);
	while (*sint != '\0')
	{
		if (!(*sint >= '0' && *sint <= '9'))
			return (1);
		new_val = *n * 10 + *sint++ - 48;
		if (new_val < *n)
			return (1);
		*n = new_val;
	}
	return (0);
}

int	parse_params(int ac, char **av, unsigned int *params)
{
	t_philo_param		param_id;

	param_id = NB_PHILO;
	--ac;
	++av;
	if (ac < PHILO_PARAM_MAX - 1)
		return (1);
	if (ac > PHILO_PARAM_MAX)
		return (1);
	while (param_id < PHILO_PARAM_MAX && ac > (int)param_id)
	{
		if (parse_uint(av[param_id], &params[param_id]) != 0)
			return (1);
		++param_id;
	}
	if (ac < 5)
		params[MAX_EAT_COUNT] = UINT_MAX;
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}
