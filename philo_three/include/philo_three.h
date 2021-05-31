#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <pthread.h>
# include <semaphore.h>
# include "lib.h"
# define FORK_NOT_OWNED 0
# define STATUS_BUFFER_SIZE 1000000

typedef enum e_philo_two_semaphore
{
	PHILO_TWO_STATE_SEMAPHORE = 0,
	PHILO_TWO_FORK_SEMAPHORE = 1,
	PHILO_TWO_SEMAPHORE_MAX	
}	t_philo_two_semaphore;

typedef struct s_philosopher
{
	int					pid;
	bool					*health_check;
	unsigned long long	id;
	t_philo_state		state;
	t_timestamp		last_meal_timestamp;
	unsigned long long	eat_count;
	sem_t				**semaphores;
}	t_philosopher;

t_philosopher		*philosophers_init(void);
void				destroy_philo_two(t_philosopher *philosophers);

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
int				thread_philo_start_range(t_philosopher *philosophers,
						unsigned long long low, unsigned long long high);

void				spawn_philosopher(t_philosopher *philo);
void				*philo_watcher(t_philosopher *philo);

/*
** SEMAPHORE 
*/

bool			semaphores_init(void);
void			semaphores_destroy(void);
sem_t			**get_semaphores(void);

#endif
