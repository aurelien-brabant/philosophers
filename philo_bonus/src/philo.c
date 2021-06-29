#include "philo_bonus.h"

void	philo_routine_eat(t_philosopher *philo)
{
	if (sem_wait(philo->sem_fork) != 0)
		return ;
	if (sem_wait(philo->sem_fork) != 0)
		return ;
	if (sem_wait(philo->sem_state) != 0)
		return ;
	output_status(" has taken a fork\n", philo);
	output_status(" has taken a fork\n", philo);
	sem_post(philo->sem_state);
	philo_change_state(philo, PHILO_STATE_EATING);
	philo->last_meal_ts = get_timestamp();
	philo->eat_count++;
	ft_msleep(philo->params[TIME_TO_EAT]);
	sem_post(philo->sem_fork);
	sem_post(philo->sem_fork);
}

void	philo_routine_sleep(t_philosopher *philo)
{
	philo_change_state(philo, PHILO_STATE_SLEEPING);
	ft_msleep(philo->params[TIME_TO_SLEEP]);
}

void	philo_routine_think(t_philosopher *philo)
{
	philo_change_state(philo, PHILO_STATE_THINKING);
}
