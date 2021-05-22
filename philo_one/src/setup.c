#include <stdlib.h>

#include "lib.h"
#include "philo_one.h"

/*
** Create the data representation of the philosophers and initialize some
** cool stuff. The address of the parameters is kept by each philosopher
** because they will need to access them inside their respective thread.
*/

static t_philosopher	*create_philosophers(unsigned long long *params)
{
	t_philosopher	*philo;
	t_philosopher	*head;
	t_philosopher	*prev;
	size_t			i;

	i = 0;
	while (i < params[NUMBER_OF_PHILOSOPHERS])
	{
		philo = malloc(sizeof (*philo));
		if (philo == NULL)
			return (destroy_philosophers(prev));
		philo->id = i + 1;
		philo->params = params;
		if (i > 0)
		{
			philo->left_philo = prev;
			philo->left_philo->right_philo = philo;
		}
		if (i++ == 0)
			head = philo;
		prev = philo;
	}
	philo->right_philo = head;
	head->left_philo = philo;
	return (head);
}

/*
** Free memory allocated for philosophers and forks representation.
** The function takes the last philosopher as an argument: that's a design
** consideration allowing easy cleanup in some error cases.
** Anyway, the last philosopher can be accessed using the first one, simply
** with first_philo->left_philo.
*/

void	*destroy_philosophers(t_philosopher *philo)
{
	t_philosopher	*cur;
	size_t			i;

	cur = philo;
	if (cur == NULL)
		return (NULL);
	i = cur->id;
	while (i > 1)
	{
		cur = cur->left_philo;
		free(cur->right_philo->right_fork);
		free(cur->right_philo);
		--i;
	}
	free(cur->right_fork);
	free(cur);
	return (NULL);
}

/*
** Call create_philosophers and create the forks, placing at the right
** place i.e at the left and right of each philosopher.
*/

t_philosopher	*dress_philosophy_table(unsigned long long *params)
{
	t_philosopher		*philo;
	t_philosopher		*prev;
	t_philosopher		*cur;
	size_t				i;

	i = 0;
	philo = create_philosophers(params);
	cur = philo;
	while (i < params[NUMBER_OF_PHILOSOPHERS])
	{
		 cur->right_fork = malloc(sizeof(t_fork));
		 if (cur->right_fork == NULL)
		 	return (destroy_philosophers(cur));
		 cur->right_fork->state = FORK_STATE_UNUSED;
		 cur->right_fork->id = i + 1;
		 if (i > 0)
		 	cur->left_fork = prev->right_fork;
		 prev = cur;
		 cur = cur->right_philo;
		 ++i;
	}
	philo->left_fork = philo->left_philo->right_fork;
	return (philo);
}
