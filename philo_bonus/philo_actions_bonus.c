#include "philo_bonus.h"

void	eat(t_philo *p)
{
	printf("%lu %u is eating\n", timestamp(), p->i + 1);
	p->timestamp_eat = timestamp();
	ft_usleep(p->time_eat);
	if (p->must_eat > 0)
		p->must_eat = p->must_eat - 1;
	sem_post(p->forks);
	sem_post(p->forks);
	return ;
}

void	philo_sleep(t_philo *p)
{
	printf("%lu %u is sleeping\n", timestamp(), p->i + 1);
	ft_usleep(p->time_sleep);
	return ;
}

void	think(t_philo *p)
{
	printf("%lu %u is thinking\n", timestamp(), p->i + 1);
	return ;
}
