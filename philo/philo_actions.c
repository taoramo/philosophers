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
	printf("%lu %u is eating\n", timestamp(), p->i + 1);
	p->timestamp_eat = timestamp();
	ft_usleep(p->time_eat);
	if (p->must_eat > 0)
		p->must_eat = p->must_eat - 1;
	pthread_mutex_unlock(&p->muteces[p->i]);
	pthread_mutex_unlock(&p->muteces[(p->i + 1) % p->n]);
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
