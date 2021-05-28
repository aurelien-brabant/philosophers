#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <pthread.h>
# include "lib.h"
# define FORK_NOT_OWNED 0

typedef enum e_philo_one_mutex
{
	PHILO_ONE_STATE_MUTEX = 0,
	PHILO_ONE_ARBITRATOR_MUTEX,
	PHILO_ONE_TOTAL_MUTEX

}	t_philo_one_mutex;

/*
** A fork is represented as a simple mutex
*/

typedef pthread_mutex_t	t_fork;

/*
** How a philosopher is represented internally for philo_one.
**
** first_fork points to the fork that the philosopher needs to lock first
** before attempting to lock second_fork. The first_fork is NOT the fork
** at the left of the philosopher, AND the second_fork is NOT the fork at
** its right. What matters here is the order in which the two forks are
** going to be locked, in order to avoid any deadlock.
*/

typedef struct s_philosopher
{
	pthread_t			thread;
	bool					*health_check;
	bool					*waiting_for_threads;
	unsigned long long	id;
	t_philo_state		state;
	t_fork				*forks;
	t_timestamp		last_meal_timestamp;
	t_fork			*first_fork;
	t_fork			*second_fork;
	unsigned long long	eat_count;
}	t_philosopher;

t_philosopher		*philosophers_init(void);
void				*destroy_philosophers(t_philosopher *philo);
void				*spawn_philosopher(t_philosopher *philo);
void				philo_change_state(t_philosopher *philo, t_philo_state new_state);
void				*philo_watcher(t_philosopher *philo);

bool				are_forks_available(t_philosopher *philo);
bool				take_fork(t_philosopher *philo, t_fork *fork);
void				drop_fork(t_fork *fork);
bool				is_fork_available(t_fork *fork);

pthread_mutex_t	*get_mutexes(void);
t_philosopher   	*get_philosophers(void);
void			output_status(const char *status, t_philosopher *philo);

/*
** ROUTINES
*/

void	philo_routine_think(t_philosopher *philo);
void	philo_routine_sleep(t_philosopher *philo);
void	philo_routine_eat(t_philosopher *philo);

#endif
