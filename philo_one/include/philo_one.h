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

typedef struct s_philosopher
{
	unsigned long long	id;
	t_fork				*left_fork;
	t_fork				*right_fork;
	struct s_philosopher	*left_philo;
	struct s_philosopher	*right_philo;
}	t_philosopher;

#endif
