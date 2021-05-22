#ifndef PHILO_ONE_H
# define PHILO_ONE_H

typedef enum e_fork_state
{
	FORK_STATE_UNUSED = 0,
	FORK_STATE_USED
}	t_fork_state;

typedef struct s_fork
{
	t_fork_state		state;
	unsigned long long	id;
}	t_fork;

typedef enum e_philo_state
{
	PHILO_STATE_DEAD = 0,
	PHILO_STATE_SLEEPING,
	PHILO_STATE_EATING,
	PHILO_STATE_THINKING,
}	t_philo_state;

typedef struct s_philosopher
{
	unsigned long long	id;
	unsigned long long	*params;
	t_philo_state		state;
	t_fork				*left_fork;
	t_fork				*right_fork;
	struct s_philosopher	*left_philo;
	struct s_philosopher	*right_philo;
}	t_philosopher;


t_philosopher	*dress_philosophy_table(unsigned long long *params);
void			*destroy_philosophers(t_philosopher *philo);

#endif
