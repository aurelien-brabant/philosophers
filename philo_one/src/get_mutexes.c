#include "philo_one.h"

/*
** Facility to get the "global" mutexes from anywhere.
*/

pthread_mutex_t *get_mutexes(void)
{
    static pthread_mutex_t  mutexes[PHILO_ONE_TOTAL_MUTEX];

    return (mutexes);
}
