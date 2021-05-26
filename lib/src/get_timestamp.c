#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>

#include "lib.h"

/*
** Get the current timestamp.
** The initial timestamp is kept internally in a static variable, and is
** initialized when the first call to get_timestamp is issued.
*/

t_timestamp	get_timestamp(void)
{
	static t_timestamp	initial_ts = 0;
	t_timestamp			current_ts;		
	struct timeval				tval;
	
	gettimeofday(&tval, NULL);
	current_ts = tval.tv_sec * 1000 + tval.tv_usec / 1000; 
	if (initial_ts == 0)
		initial_ts = current_ts;
	return (current_ts - initial_ts);
}
