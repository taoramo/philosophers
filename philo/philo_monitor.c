#include "philo.h"

int	is_finished(t_philo **arr)
{
	int	i;

	i = 0;
	while (i < arr[0]->n)
	{
		if (arr[i]->must_eat != 0)
			return (0);
		i++;
	}
	*arr[0]->death = 1;
	return (1);
}

void	check_death(t_philo **arr)
{
	int	i;

	i = 0;
	while (i < arr[0]->n)
	{
		if (timestamp() - arr[i]->timestamp_eat > arr[i]->time_die)
		{
			*arr[0]->death = 1;
			printf("%lu %u has died\n", timestamp(), i + 1);
			break ;
		}
		i++;
	}
}

void	*philo_monitor(void *arg)
{
	t_philo	**arr;

	arr = (t_philo **)arg;
	ft_usleep(arr[0]->time_die / 2);
	while (1)
	{
		if (is_finished(arr))
			return (0);
		check_death(arr);
		if (*arr[0]->death == 1)
			return (0);
		usleep(1000);
	}
}
