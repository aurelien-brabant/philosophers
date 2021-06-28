#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

#include "philo.h"

const char	*get_state_string(t_philo_state state)
{
	if (state == PHILO_STATE_EATING)
		return (" is eating\n");
	if (state == PHILO_STATE_DEAD)
		return (" \033[1;31mdied\033[0m\n");
	if (state == PHILO_STATE_SLEEPING)
		return (" is sleeping\n");
	if (state == PHILO_STATE_THINKING)
		return (" is thinking\n");
	return (NULL);
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

bool	parse_params(int ac, char **av, unsigned int *params)
{
	t_philo_param		param_id;

	param_id = NUMBER_OF_PHILOSOPHERS;
	--ac;
	++av;
	if (ac < PHILO_PARAM_MAX - 1)
		return (false);
	if (ac > PHILO_PARAM_MAX)
		return (false);
	while (param_id < PHILO_PARAM_MAX && ac > (int)param_id)
	{
		if (parse_uint(av[param_id], &params[param_id]) != 0)
			return (false);
		++param_id;
	}
	if (ac < 5)
		params[NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT] = UINT_MAX;
	return (true);
}

void	ft_msleep(unsigned long long duration_in_ms)
{
	t_timestamp	start_ts;
	t_timestamp	current_ts;
	t_timestamp	end_ts;

	start_ts = get_timestamp();
	end_ts = start_ts + duration_in_ms;
	while (1)
	{
		current_ts = get_timestamp();
		if (current_ts >= end_ts)
			break ;
		usleep(100);
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		++i;
	return (i);
}
