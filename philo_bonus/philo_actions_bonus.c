/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:53:19 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:53:20 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat(t_philo *p)
{
	sem_wait(p->print);
	printf("%lu %u has taken a fork\n%lu %u is eating\n",
		timestamp(p), p->i + 1, timestamp(p), p->i + 1);
	sem_post(p->print);
	sem_wait(p->time);
	p->timestamp_eat = timestamp(p);
	sem_post(p->time);
	ft_usleep(p->time_eat);
	if (p->must_eat > 0)
		p->must_eat = p->must_eat - 1;
	sem_post(p->forks);
	sem_post(p->forks);
	return ;
}

void	philo_sleep(t_philo *p)
{
	philo_print(p, "is sleeping");
	ft_usleep(p->time_sleep);
	return ;
}

void	think(t_philo *p)
{
	philo_print(p, "is thinking");
	return ;
}
