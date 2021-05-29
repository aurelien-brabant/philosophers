#ifndef PHILO_TWO_H
# define PHILO_TWO_H
# include <pthread.h>
# include "lib.h"
# define FORK_NOT_OWNED 0
# define STATUS_BUFFER_SIZE 1000000

typedef struct s_philosopher
{
	pthread_t			thread;
	bool					*health_check;
	unsigned long long	id;
	t_philo_state		state;
	t_timestamp		last_meal_timestamp;
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
int				thread_philo_start(t_philosopher *philosophers);

void				*spawn_philosopher(t_philosopher *philo);
void				*philo_watcher(t_philosopher *philo);

/*
** MUTEX
*/

void				init_mutexes(void);
void				destroy_mutexes(void);
pthread_mutex_t	*get_mutexes(void);

#endif
