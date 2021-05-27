#include <unistd.h>

#include "philo_one.h"

static size_t	int_char_size(unsigned long long n)
{
	size_t	i;

	i = 1;
	while (n / 10)
	{
		++i;
		n /= 10;	
	}
	return (i);
}

void	concat_int(char **buf, unsigned long long n)
{
	size_t	i;
	size_t	char_size;

	char_size = int_char_size(n);
	i = char_size - 1;
	while (1)
	{
		(*buf)[i] = n % 10 + 48; 
		if (i-- == 0)
			break ;
		n /= 10;
	}
	*buf += char_size;
}

void	concat_str(char **buf, const char *s)
{
	while (*s != '\0')
	{
		**buf = *s++;
		*buf += 1;
	}
}

void	output_status(const char *status, t_philosopher *philo)
{
	static char		buf[100000];
	char				*buf_pos;
	
	if (philo == NULL)
		return ;
	buf_pos = buf;
	pthread_mutex_lock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);
	if (*philo->health_check)
	{
		concat_int(&buf_pos, get_timestamp());
		concat_str(&buf_pos, "ms ");
		concat_int(&buf_pos, philo->id);
		concat_str(&buf_pos, status);
		*buf_pos = '\0';
		write(STDOUT_FILENO, buf, ft_strlen(buf));
	}
	pthread_mutex_unlock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);
}
