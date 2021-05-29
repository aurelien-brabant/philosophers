#include "philo_two.h"

static void	take_fork(t_philosopher *philo)
{
	sem_wait(get_semaphores()[PHILO_TWO_STATE_SEMAPHORE]);
	output_status(" has taken a fork\n", philo);
	sem_post(get_semaphores()[PHILO_TWO_STATE_SEMAPHORE]);
}

void	philo_routine_eat(t_philosopher *philo)
{
	sem_t	*fork;

	fork = get_semaphores()[PHILO_TWO_FORK_SEMAPHORE];
	sem_wait(fork);
	take_fork(philo);
	sem_wait(fork);
	take_fork(philo);
	philo->last_meal_timestamp = get_timestamp();
	philo->eat_count++;
	philo_change_state(philo, PHILO_STATE_EATING);
	ft_msleep(get_params()[TIME_TO_EAT]);
	sem_post(fork);
	sem_post(fork);
}

void	philo_routine_sleep(t_philosopher *philo)
{
	philo_change_state(philo, PHILO_STATE_SLEEPING);
	ft_msleep(get_params()[TIME_TO_SLEEP]);
}

void	philo_routine_think(t_philosopher *philo)
{
	philo_change_state(philo, PHILO_STATE_THINKING);
}
