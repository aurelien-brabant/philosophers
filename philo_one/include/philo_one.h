#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <pthread.h>
# include "lib.h"

typedef enum e_fork_state
{
	FORK_STATE_UNUSED = 0,
	FORK_STATE_USED
}	t_fork_state;

typedef enum e_philo_one_mutex
{
	PHILO_ONE_STATE_MUTEX = 0,
	PHILO_ONE_TOTAL_MUTEX

}	t_philo_one_mutex;

typedef struct s_fork
{
	t_fork_state		state;
	unsigned long long	id;
	pthread_mutex_t		mutex;
}	t_fork;

/*
** waiting_for_threads: set to true until all the threads have been created.
*/

typedef struct s_philosopher
{
	pthread_t			thread;
	pthread_mutex_t		*mutexes;
	bool					*health_check;
	bool					*waiting_for_threads;
	unsigned long long	id;
	unsigned long long	*params;
	t_philo_state		state;
	t_fork				*left_fork;
	t_fork				*right_fork;
	struct s_philosopher	*left_philo;
	struct s_philosopher	*right_philo;

	unsigned long long	last_meal_timestamp;
}	t_philosopher;

void			*destroy_philosophers(t_philosopher *philo);
void			*spawn_philosopher(t_philosopher *philo);
t_philosopher	*dress_philosophy_table(unsigned long long *params, pthread_mutex_t *mutexes);
void			philo_change_state(t_philosopher *philo, t_philo_state new_state, unsigned long long *ts);
void			*philo_watcher(t_philosopher *philo);

bool			are_forks_available(t_philosopher *philo);
bool			take_fork(t_philosopher *philo, t_fork *fork);
void			drop_fork(t_fork *fork);
bool			is_fork_available(t_fork *fork);

#endif
