/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:52:28 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:52:30 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *p)
{
	if (is_dead(p))
	{
		pthread_mutex_unlock(&p->muteces[p->i]);
		pthread_mutex_unlock(&p->muteces[(p->i + 1) % p->n]);
		return ;
	}
	printf("%lu %u has taken a fork\n", timestamp(p), p->i + 1);
	printf("%lu %u is eating\n", timestamp(p), p->i + 1);
	pthread_mutex_lock(&p->time_mutex[p->i]);
	p->timestamp_eat = timestamp(p);
	if (p->must_eat > 0)
		p->must_eat = p->must_eat - 1;
	pthread_mutex_unlock(&p->time_mutex[p->i]);
	ft_usleep(p->time_eat);
	pthread_mutex_unlock(&p->muteces[p->i]);
	pthread_mutex_unlock(&p->muteces[(p->i + 1) % p->n]);
}

void	philo_sleep(t_philo *p)
{
	printf("%lu %u is sleeping\n", timestamp(p), p->i + 1);
	ft_usleep(p->time_sleep);
	return ;
}

void	think(t_philo *p)
{
	printf("%lu %u is thinking\n", timestamp(p), p->i + 1);
	return ;
}

int	is_dead(t_philo *p)
{
	int	result;

	result = 0;
	pthread_mutex_lock(p->death_mutex);
	if (*p->death == 1)
		result = 1;
	pthread_mutex_unlock(p->death_mutex);
	return (result);
}
