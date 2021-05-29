#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib.h"

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
