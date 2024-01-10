/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:52:53 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:52:54 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philosopher_odd(t_philo *p)
{
	pthread_mutex_lock(&p->time_mutex[p->i]);
	while (p->must_eat)
	{
		pthread_mutex_unlock(&p->time_mutex[p->i]);
		pthread_mutex_lock(&p->muteces[p->i]);
		if (is_dead(p))
		{
			pthread_mutex_unlock(&p->muteces[p->i]);
			break ;
		}
		printf("%lu %u has taken a fork\n", timestamp(p), p->i + 1);
		pthread_mutex_lock(&p->muteces[(p->i + 1) % p->n]);
		eat(p);
		if (is_dead(p))
			break ;
		philo_sleep(p);
		if (is_dead(p))
			break ;
		think(p);
		pthread_mutex_lock(&p->time_mutex[p->i]);
	}
}

void	philosopher_even(t_philo *p)
{
	pthread_mutex_lock(&p->time_mutex[p->i]);
	while (p->must_eat)
	{
		pthread_mutex_unlock(&p->time_mutex[p->i]);
		if (is_dead(p))
			break ;
		philo_sleep(p);
		pthread_mutex_lock(&p->muteces[p->i]);
		if (is_dead(p))
		{
			pthread_mutex_unlock(&p->muteces[p->i]);
			break ;
		}
		printf("%lu %u has taken a fork\n", timestamp(p), p->i + 1);
		pthread_mutex_lock(&p->muteces[(p->i + 1) % p->n]);
		eat(p);
		if (is_dead(p))
			break ;
		think(p);
		pthread_mutex_lock(&p->time_mutex[p->i]);
	}
}

void	philosopher_alone(t_philo *p)
{
	pthread_mutex_lock(&p->time_mutex[p->i]);
	while (p->must_eat)
	{
		pthread_mutex_unlock(&p->time_mutex[p->i]);
		if (is_dead(p))
			break ;
		philo_sleep(p);
		pthread_mutex_lock(&p->muteces[p->i]);
		if (is_dead(p))
		{
			pthread_mutex_unlock(&p->muteces[p->i]);
			break ;
		}
		printf("%lu %u has taken a fork\n", timestamp(p), p->i + 1);
		while (is_dead(p) == 0)
			ft_usleep(100);
		break ;
		think(p);
		pthread_mutex_lock(&p->time_mutex[p->i]);
	}
}

void	*philosopher(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->n == 1)
		philosopher_alone(p);
	else if (p->i % 2)
		philosopher_odd(p);
	else
		philosopher_even(p);
	return (0);
}
