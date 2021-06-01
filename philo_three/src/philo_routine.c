#include "philo_three.h"
#include <stdio.h>

void	philo_routine_eat(t_philosopher *philo)
{
	sem_t	*fork_sem;
	sem_t	*state_sem;

	fork_sem = get_semaphores()[PHILO_THREE_SEM_FORK];
	state_sem = get_semaphores()[PHILO_THREE_SEM_STATE];
	ft_sem_wait(fork_sem);
	ft_sem_wait(fork_sem);
	ft_sem_wait(state_sem);
	output_status(" has taken a fork\n", philo);
	output_status(" has taken a fork\n", philo);
	philo_change_state(philo, PHILO_STATE_EATING);
	ft_sem_post(state_sem);
	philo->last_meal_timestamp = get_timestamp();
	philo->eat_count++;
	ft_msleep(get_params()[TIME_TO_EAT]);
	ft_sem_post(fork_sem);
	ft_sem_post(fork_sem);
}

void	philo_routine_sleep(t_philosopher *philo)
{
	sem_t	*state_sem;

	state_sem = get_semaphores()[PHILO_THREE_SEM_STATE];
	ft_sem_wait(state_sem);
	philo_change_state(philo, PHILO_STATE_SLEEPING);
	ft_sem_post(state_sem);
	ft_msleep(get_params()[TIME_TO_SLEEP]);
}

void	philo_routine_think(t_philosopher *philo)
{
	sem_t	*state_sem;

	state_sem = get_semaphores()[PHILO_THREE_SEM_STATE];
	ft_sem_wait(state_sem);
	philo_change_state(philo, PHILO_STATE_THINKING);
	ft_sem_post(state_sem);
}
