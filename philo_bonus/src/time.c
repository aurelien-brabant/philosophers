#include <sys/time.h>
#include <unistd.h>

#include "philo_bonus.h"

t_timestamp	get_timestamp(void)
{
	static t_timestamp	initial_ts = 0;
	t_timestamp			current_ts;		
	struct timeval		tval;

	gettimeofday(&tval, NULL);
	current_ts = tval.tv_sec * 1000 + tval.tv_usec / 1000;
	if (initial_ts == 0)
		initial_ts = current_ts;
	return (current_ts - initial_ts);
}

/*
** Millisecond sleep - wait a given number of milliseconds using
** fragmented usleep calls. This is an hacky way to play with the kernel's
** scheduler to reduce usleep wake up delay.
** ft_msleep is only used to wait for each philosopher action to be completed.
** usleep is still used to make the program rest and save many cpu cycles
** while in loop (in the monitoring loop for example).
*/

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
