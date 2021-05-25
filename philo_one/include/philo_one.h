#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <pthread.h>
# include "lib.h"

typedef enum e_fork_state
{
	FORK_STATE_UNUSED = 0,
	FORK_STATE_USED,
	FORK_NOT_OWNED,
}	t_fork_state;

typedef enum e_philo_one_mutex
{
	PHILO_ONE_STATE_MUTEX = 0,
	PHILO_ONE_TOTAL_MUTEX

}	t_philo_one_mutex;

typedef struct s_fork
{
	t_fork_state		state;
	unsigned long long	owner;
	unsigned long long	id;
	pthread_mutex_t		mutex;
}	t_fork;

/*
** waiting_for_threads: set to true until all the threads have been created.
*/

typedef struct s_philosopher
{
	pthread_t			thread;
	bool					*health_check;
	bool					*waiting_for_threads;
	unsigned long long	id;
	t_philo_state		state;
	t_fork				*left_fork;
	t_fork				*right_fork;
	unsigned long long	last_meal_timestamp;
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

#endif
