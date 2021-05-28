#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <pthread.h>
# include "lib.h"
# define FORK_NOT_OWNED 0
# define STATUS_BUFFER_SIZE 1000000

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
void				destroy_philo_one(t_philosopher *philosophers);

void				philo_change_state(t_philosopher *philo, t_philo_state new_state);
void				output_status(const char *status, t_philosopher *philo);

/*
** ROUTINES
*/

void				philo_routine_think(t_philosopher *philo);
void				philo_routine_sleep(t_philosopher *philo);
void				philo_routine_eat(t_philosopher *philo);

/*
** THREAD
*/

void				thread_terminate_simulation(t_philosopher *philosophers);
int				thread_philo_start_parity(t_philosopher *philosophers, bool start_even_first);

void				*spawn_philosopher(t_philosopher *philo);
void				*philo_watcher(t_philosopher *philo);

/*
** MUTEX
*/

void				init_mutexes(void);
void				destroy_mutexes(void);
pthread_mutex_t	*get_mutexes(void);

#endif
