#include "philo.h"

void	philosopher_odd(t_philo *p)
{
	p->timestamp_eat = timestamp();
	while (p->must_eat)
	{
		pthread_mutex_lock(&p->muteces[p->i]);
		if (*p->death == 1)
			break ;
		printf("%lu %u has taken a fork\n", timestamp(), p->i + 1);
		pthread_mutex_lock(&p->muteces[(p->i + 1) % p->n]);
		if (*p->death == 1)
		{
			pthread_mutex_unlock(&p->muteces[p->i]);
			pthread_mutex_unlock(&p->muteces[(p->i + 1) % p->n]);
			break ;
		}
		eat(p);
		if (*p->death == 1)
			break ;
		philo_sleep(p);
		if (*p->death == 1)
			break ;
		think(p);
	}
}

void	philosopher_even(t_philo *p)
{
	p->timestamp_eat = timestamp();
	while (p->must_eat)
	{
		if (*p->death == 1)
			break ;
		philo_sleep(p);
		pthread_mutex_lock(&p->muteces[p->i]);
		if (*p->death == 1)
			break ;
		printf("%lu %u has taken a fork\n", timestamp(), p->i + 1);
		pthread_mutex_lock(&p->muteces[(p->i + 1) % p->n]);
		if (*p->death == 1)
		{
			pthread_mutex_unlock(&p->muteces[p->i]);
			pthread_mutex_unlock(&p->muteces[(p->i + 1) % p->n]);
			break ;
		}
		eat(p);
		if (*p->death == 1)
			break ;
		think(p);
	}
}

void	*philosopher(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->i % 2)
		philosopher_odd(p);
	else
		philosopher_even(p);
	return (0);
}
