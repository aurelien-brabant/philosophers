#include "philo_one.h"

void	philo_routine_eat(t_philosopher *philo)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	left_fork = &philo->forks[philo->id - 1];
	right_fork = &philo->forks[philo->id % get_params()[NUMBER_OF_PHILOSOPHERS]];
	pthread_mutex_lock(&left_fork->mutex);
	pthread_mutex_lock(&right_fork->mutex);
	output_status(" has taken a fork\n", philo);
	output_status(" has taken a fork\n", philo);
	philo->last_meal_timestamp = get_timestamp();
	philo_change_state(philo, PHILO_STATE_EATING);
	ft_usleep(get_params()[TIME_TO_EAT]);
	pthread_mutex_unlock(&left_fork->mutex);
	pthread_mutex_unlock(&right_fork->mutex);
}

void	philo_routine_sleep(t_philosopher *philo)
{
	philo_change_state(philo, PHILO_STATE_SLEEPING);
	ft_usleep(get_params()[TIME_TO_SLEEP]);
}

void	philo_routine_think(t_philosopher *philo)
{
	philo_change_state(philo, PHILO_STATE_THINKING);
}
