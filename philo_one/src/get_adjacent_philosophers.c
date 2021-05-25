#include "philo_one.h"

/*
** Get the philosophers that are sitting next to the philosopher
** which's id is passed.
** The addresses of the two philosophers are put in the adjs array which is
** is assumed to have a size of two.
**
** the number of adjacent philosophers is returned, which is usually 2. However
** if there are only two philosophers then 1 is going to be returned.
** The address of the only adjacent philosopher is going to be 
** placed two times in adjs.
*/

int get_adjacent_philosophers(unsigned long long id, t_philosopher **adjs)
{
    t_philosopher       *philosophers;
    unsigned long long  nb_of_philo;

    philosophers = get_philosophers();
    nb_of_philo = get_params()[NUMBER_OF_PHILOSOPHERS];
    if (id == 1)
        adjs[0] = &philosophers[nb_of_philo - 1];
    else
        adjs[0] = &philosophers[id - 1];
    if (id == nb_of_philo)
        adjs[1] = &philosophers[0];
    else
        adjs[1] = &philosophers[id + 1];
    return (2 - (nb_of_philo == 2))
}
