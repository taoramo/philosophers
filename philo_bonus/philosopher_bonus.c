#include "philo_bonus.h"

void	init_threads(t_philo *p, pthread_t *monitor, pthread_t *death)
{
	if (pthread_create(monitor, 0, &philo_monitor, p) != 0
		|| pthread_create(death, 0, &ft_death, p) != 0)
	{
		printf("Error creating monitor thread\n");
		free(p->pids);
		free(p);
		exit(4);
	}
}

void	join_threads(t_philo *p, pthread_t monitor, pthread_t death)
{
	if (pthread_join(monitor, 0) != 0 || pthread_join(death, 0) != 0)
	{
		printf("Error joining monitor thread\n");
		free(p->pids);
		free(p);
		exit(5);
	}
}

void	philosopher_odd(t_philo *p)
{
	pthread_t	monitor;
	pthread_t	death;

	init_threads(p, &monitor, &death);
	p->timestamp_eat = timestamp();
	while (p->must_eat)
	{
		sem_wait(p->forks);
		printf("%lu %u has taken a fork\n", timestamp(), p->i + 1);
		sem_wait(p->forks);
		eat(p);
		if (p->must_eat)
		{
			philo_sleep(p);
			think(p);
		}
	}
	join_threads(p, monitor, death);
}

void	philosopher_even(t_philo *p)
{
	pthread_t	monitor;
	pthread_t	death;

	init_threads(p, &monitor, &death);
	p->timestamp_eat = timestamp();
	while (p->must_eat)
	{
		philo_sleep(p);
		sem_wait(p->forks);
		printf("%lu %u has a taken fork\n", timestamp(), p->i + 1);
		sem_wait(p->forks);
		eat(p);
		if (p->must_eat)
			think(p);
	}
	join_threads(p, monitor, death);
}

void	*philosopher(void *arg)
{
	t_philo	*p;
	int		i;
	sem_t	*forks;

	p = (t_philo *)arg;
	forks = sem_open("/forks", 0);
	if (forks == SEM_FAILED)
		free_philo(p, 1);
	p->forks = forks;
	i = 0;
	while (i < p->n)
	{
		if (p->pids[i] == 0)
			p->i = i;
		if (p->i == i && i % 2 == 1)
			philosopher_odd(p);
		if (p->i == i && i % 2 == 0)
			philosopher_even(p);
		i++;
	}
	free(p->pids);
	free(p);
	exit(0);
	return (0);
}
