#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# define STATUS_BUFFER_SIZE 1000000
# include <stdbool.h>

typedef enum e_philo_param
{
	NUMBER_OF_PHILOSOPHERS = 0,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT,
	PHILO_PARAM_MAX
}	t_philo_param;

typedef enum e_philo_state
{
	PHILO_STATE_DEAD = 0,
	PHILO_STATE_SLEEPING,
	PHILO_STATE_EATING,
	PHILO_STATE_THINKING,
}	t_philo_state;

typedef enum e_philo_error
{
	ERROR_ARGS_PARSING = 0,
	ERROR_MUTEX_INIT,
	ERROR_MUTEX_CLOSE,
	ERROR_PHILOSOPHERS_INIT,
	ERROR_THREAD_CREATE,
	ERROR_THREAD_DETACH,
	ERROR_THREAD_JOIN,
}	t_philo_error;

/*
** A fork is represented as a simple mutex
*/

typedef pthread_mutex_t	t_fork;

typedef unsigned long long int	t_timestamp;

typedef struct s_philosopher
{
	pthread_t			thread;
	pthread_mutex_t		*out_mutex;
	bool				*health_check;
	bool				*waiting_for_threads;
	unsigned long long	id;
	t_philo_state		state;
	t_fork				*forks;
	t_timestamp			last_meal_timestamp;
	t_fork				*first_fork;
	t_fork				*second_fork;
	unsigned long long	eat_count;
}	t_philosopher;


size_t				ft_strlen(const char *s);
int					dputs(const char *s, int fd);
bool				parse_params(int ac, char **av);
t_timestamp			get_timestamp(void);
unsigned long long	*get_params(void);
void				ft_msleep(unsigned long long ms);
const char			*get_state_string(t_philo_state state);
bool				parse_uint(const char *sint, unsigned long long *n);


t_philosopher		*philosophers_init(void);
void				destroy_simulation(t_philosopher *philosophers);

void				philo_change_state(t_philosopher *philo,
						t_philo_state new_state);
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

int					thread_philo_start_odd(t_philosopher *philosophers);
int					thread_philo_start_even(t_philosopher *philosophers);
void				thread_terminate_simulation(t_philosopher *philosophers);

void				*spawn_philosopher(t_philosopher *philo);
void				*philo_watcher(t_philosopher *philo);

/*
** MUTEX
*/

bool				init_mutexes(void);
size_t				destroy_mutexes(void);
pthread_mutex_t		*get_mutexes(void);


int	philo_error_print(t_philo_error philo_error);

#endif
