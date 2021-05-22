#include <stdlib.h>

#include "philo_one.h"
#include "lib.h"

static void	*destroy_philosophers(t_philosopher *philo)
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

static t_philosopher	*create_philosophers(unsigned long long philo_nb)
{
	t_philosopher	*philo;
	t_philosopher	*head;
	t_philosopher	*prev;
	size_t			i;

	i = 0;
	while (i < philo_nb)
	{
		philo = malloc(sizeof (*philo));
		if (philo == NULL)
			return (destroy_philosophers(prev));
		philo->id = i + 1;
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

static t_philosopher	*dress_philosophy_table(unsigned long long philo_nb)
{
	t_philosopher		*philo;
	t_philosopher		*prev;
	t_philosopher		*cur;
	size_t				i;

	i = 0;
	philo = create_philosophers(philo_nb);
	cur = philo;
	while (i < philo_nb)
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

int	main(int ac, char **av)
{
	unsigned long long	params[PHILO_PARAM_MAX];
	t_philosopher		*philo;

	if (!parse_params(ac, av, params))
		return (1);
	philo = dress_philosophy_table(params[NUMBER_OF_PHILOSOPHERS]);
	if (philo == NULL)
		return (1);
	destroy_philosophers(philo->left_philo);
	return (0);
}
