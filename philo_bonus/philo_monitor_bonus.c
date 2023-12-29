#include "philo_bonus.h"

int	check_death(t_philo *p)
{
	if (timestamp() - p->timestamp_eat > p->time_die
		&& p->timestamp_eat != 0)
	{
		printf("%lu %u has died\n", timestamp(), p->i + 1);
		return (1);
	}
	return (0);
}

void	*philo_monitor(void *arg)
{
	t_philo	*p;
	sem_t	*death;

	p = (t_philo *)arg;
	death = sem_open("/death", 0);
	ft_usleep(p->time_die / 2);
	while (1)
	{
		if (check_death(p))
		{
			sem_post(death);
			return (0);
		}
		if (p->must_eat == 0)
		{
			free(p->pids);
			free(p);
			exit(0);
		}
		usleep(1000);
	}
}
