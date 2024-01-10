/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:53:45 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:53:46 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_death(t_philo *p)
{
	sem_t	*death;

	death = sem_open("/death", 0);
	sem_wait(p->time);
	if (timestamp(p) - p->timestamp_eat > p->time_die
		&& p->timestamp_eat != 0)
	{
		sem_post(p->time);
		printf("%lu %u has died\n", timestamp(p), p->i + 1);
		sem_post(death);
		return (1);
	}
	sem_post(p->time);
	return (0);
}

void	*philo_monitor(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	while (1)
	{
		if (check_death(p))
		{
			return (0);
		}
		sem_wait(p->time);
		if (p->must_eat == 0)
		{
			sem_post(p->time);
			return (0);
		}
		sem_post(p->time);
		usleep(5000);
	}
	return (0);
}
