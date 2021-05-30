#include "philo_one.h"

void	philo_routine_eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->first_fork);
	pthread_mutex_lock(philo->second_fork);
	pthread_mutex_lock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);
	output_status(" has taken a fork\n", philo);
	output_status(" has taken a fork\n", philo);
	philo_change_state(philo, PHILO_STATE_EATING);
	pthread_mutex_unlock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);
	philo->last_meal_timestamp = get_timestamp();
	philo->eat_count++;
	ft_msleep(get_params()[TIME_TO_EAT]);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	philo_routine_sleep(t_philosopher *philo)
{
	pthread_mutex_lock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);
	philo_change_state(philo, PHILO_STATE_SLEEPING);
	pthread_mutex_unlock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);
	ft_msleep(get_params()[TIME_TO_SLEEP]);
}

void	philo_routine_think(t_philosopher *philo)
{
	pthread_mutex_lock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);
	philo_change_state(philo, PHILO_STATE_THINKING);
	pthread_mutex_unlock(&get_mutexes()[PHILO_ONE_STATE_MUTEX]);
}
