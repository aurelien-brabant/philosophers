#include "philo_three.h"
#include <stdio.h>

void	philo_routine_eat(t_philosopher *philo, sem_t *state_sem, sem_t *fork_sem)
{
	sem_wait(fork_sem);
	sem_wait(fork_sem);
	sem_wait(state_sem);
	printf("Going to output status\n");
	//output_status(" has taken a fork\n", philo);
	//output_status(" has taken a fork\n", philo);
	//philo_change_state(philo, PHILO_STATE_EATING);
	sem_post(state_sem);
	philo->last_meal_timestamp = get_timestamp();
	philo->eat_count++;
	ft_msleep(philo->params[TIME_TO_EAT]);
	sem_post(fork_sem);
	sem_post(fork_sem);
}

void	philo_routine_sleep(t_philosopher *philo, sem_t *state_sem)
{
	sem_wait(state_sem);
	philo_change_state(philo, PHILO_STATE_SLEEPING);
	sem_post(state_sem);
	ft_msleep(philo->params[TIME_TO_SLEEP]);
}

void	philo_routine_think(t_philosopher *philo, sem_t *state_sem)
{
	sem_wait(state_sem);
	philo_change_state(philo, PHILO_STATE_THINKING);
	sem_post(state_sem);
}
