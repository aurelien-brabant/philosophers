#include "philo_one.h"

t_philosopher   *get_philosophers(void)
{
    static t_philosopher    *philosophers = NULL;

    if (philosophers == NULL)
        philosophers = philosophers_init();
    return (philosophers);
}
