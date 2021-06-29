#ifndef PHILO_THREE_H
# define PHILO_THREE_H
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>

# define FORK_NOT_OWNED 0
# define STATUS_BUFFER_SIZE 10000
# define ERROR_PREFIX "\033[1;31mError: \033[0m"

# define SEM_NM_FORK "/fork"
# define SEM_NM_STATE "/state"

# define EXIT_CHILD_HAS_EATEN 0
# define EXIT_CHILD_DIED 1

typedef enum e_philo_param
{
	NB_PHILO = 0,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	MAX_EAT_COUNT,
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
	ERROR_SEM_OPEN,
	ERROR_SEM_CLOSE,
	ERROR_SEM_UNLINK,
	ERROR_SEM_POST,
	ERROR_SEM_WAIT,
	ERROR_PHILOSOPHERS_INIT,
	ERROR_THREAD_CREATE,
	ERROR_THREAD_DETACH,
	ERROR_THREAD_JOIN,
	ERROR_FORK,
}	t_philo_error;

typedef enum e_philo_two_semaphore
{
	PHILO_THREE_SEM_STATE = 0,
	PHILO_THREE_SEM_FORK,
	PHILO_THREE_SEM_MAX
}	t_philo_two_semaphore;


typedef unsigned long long int	t_timestamp;

typedef struct s_philosopher
{
	unsigned int			id;
	sem_t					*sem_state;
	sem_t					*sem_fork;
	unsigned int			*params;
	int						pid;
	t_philo_state			state;
	t_timestamp				last_meal_ts;
	unsigned int			eat_count;
	bool					is_at_table;
	struct s_philosopher	*philosophers;
}	t_philosopher;

void				philo_change_state(t_philosopher *philo, 
						t_philo_state new_state);
void				output_status(const char *status, t_philosopher *philo);

int					philo_error_print(t_philo_error error);

size_t				ft_strlen(const char *s);
int					parse_params(int ac, char **av, unsigned int *params);
const char			*get_state_string(t_philo_state state);
int					parse_uint(const char *sint, unsigned int *n);

t_timestamp			get_timestamp(void);
void				ft_msleep(unsigned long long ms);

void				philo_routine_think(t_philosopher *philo);
void				philo_routine_sleep(t_philosopher *philo);
void				philo_routine_eat(t_philosopher *philo);

void				process_kill_children(t_philosopher *philosophers);
void				process_start_children(t_philosopher *philosophers);
void				process_wait_for_children(t_philosopher *philosophers);

void				spawn_philosopher(t_philosopher *philo);
void				*philo_watcher(t_philosopher *philo);

#endif
