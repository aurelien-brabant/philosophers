#include <unistd.h>

#include "philo_two.h"

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

static void	concat_int(char **buf, unsigned long long n)
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

static void	concat_str(char **buf, const char *s)
{
	while (*s != '\0')
	{
		**buf = *s++;
		*buf += 1;
	}
}

/*
** Output the status of a philosopher, as asked by the subject.
** The output is presented in the following fashion:
** <TIMESTAMP> <PHILOSOPHER_ID> <ACTION>
** A single call to write is issued instead of a complicated printf one,
** in order to avoid performance issues.
**
** A big static buffer is allocated in order to hold the entire string which
** is going to be outputed. Functions such as concat_str and concat_int are
** here to build this string. The fact the buffer is static means that it is
** going to be allocated at the first call only, and not at every call, which
** highly reduces the produced overhead. output_status(NULL, NULL) is issued
** in the initialization phase to allocate the buffer before the actual
** simulation begins.
*/

void	output_status(const char *status, t_philosopher *philo)
{
	static char		buf[STATUS_BUFFER_SIZE];
	char			*buf_pos;

	if (philo == NULL)
		return ;
	buf_pos = buf;
	if (*philo->health_check)
	{
		concat_str(&buf_pos, "\033[1;40m");
		concat_int(&buf_pos, get_timestamp());
		concat_str(&buf_pos, "\033[0m ");
		concat_int(&buf_pos, philo->id);
		concat_str(&buf_pos, status);
		*buf_pos = '\0';
		write(STDOUT_FILENO, buf, buf_pos - buf);
	}
}
