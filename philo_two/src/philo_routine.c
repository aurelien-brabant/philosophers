#include "philo_two.h"

static void	take_fork(t_philosopher *philo)
{
	output_status(" has taken a fork\n", philo);
}

void	philo_routine_eat(t_philosopher *philo)
{
	take_fork(philo);
	take_fork(philo);
	philo->last_meal_timestamp = get_timestamp();
	philo->eat_count++;
	philo_change_state(philo, PHILO_STATE_EATING);
	ft_msleep(get_params()[TIME_TO_EAT]);
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
