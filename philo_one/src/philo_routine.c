#include "philo_one.h"

void	philo_routine_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->second_fork);
	output_status(" has taken a fork\n", philo);
	output_status(" has taken a fork\n", philo);
	philo->last_meal_timestamp = get_timestamp();
	philo_change_state(philo, PHILO_STATE_EATING);
	ft_usleep(get_params()[TIME_TO_EAT]);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
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
