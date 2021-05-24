#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>

unsigned long long	get_timestamp(bool can_initialize)
{
	static unsigned long long	initial_timestamp = 0;
	unsigned long long			timestamp;
	struct timeval				tval;
	
	gettimeofday(&tval, NULL);
	timestamp = tval.tv_sec * 1000 + tval.tv_usec / 1000; 
	if (initial_timestamp == 0)
	{
		if (can_initialize)
			initial_timestamp = timestamp;
		return (0);
	}
	return (timestamp - initial_timestamp);
}
