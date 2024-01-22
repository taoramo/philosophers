/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:54:12 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:54:13 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (pthread_detach(*death) != 0)
		printf("Error detaching death thread\n");
	if (pthread_detach(*monitor) != 0)
		printf("Error detaching monitor thread\n");
}

void	free_resources(t_philo *p)
{
	sem_close(p->time);
	free(p->pids);
	free(p);
	exit(0);
}

void	philosopher_routine(t_philo *p)
{
	pthread_t	monitor;
	pthread_t	death;

	init_threads(p, &monitor, &death);
	think(p);
	while (p->must_eat)
	{
		sem_wait(p->forks);
		philo_print(p, "has taken a fork");
		sem_wait(p->forks);
		eat(p);
		if (p->must_eat)
		{
			philo_sleep(p);
			think(p);
		}
	}
	free_resources(p);
	exit(0);
}

void	*philosopher(void *arg)
{
	t_philo	*p;
	int		i;

	p = (t_philo *)arg;
	i = 0;
	while (i < p->n)
	{
		if (p->pids[i] == 0)
			p->i = i;
		i++;
	}
	open_semaphores(p);
	i = 0;
	while (i < p->n)
	{
		if (p->i == i && i % 2 == 1)
			philosopher_routine(p);
		if (p->i == i && i % 2 == 0)
			philosopher_routine(p);
		i++;
	}
	free(p->pids);
	free(p);
	exit(0);
	return (0);
}
