/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:52:46 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:52:47 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long int	sys_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

unsigned long int	timestamp(t_philo *p)
{
	return (sys_timestamp() - p->timestamp_start);
}

int	ft_usleep(unsigned long milliseconds)
{
	unsigned long	start;

	start = sys_timestamp();
	while ((sys_timestamp() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	set_start_time(t_philo **arr)
{
	unsigned int		i;
	unsigned long int	time_start;

	time_start = sys_timestamp();
	i = 0;
	while (i < arr[0]->n)
	{
		arr[i]->timestamp_start = time_start;
		arr[i]->timestamp_eat = 0;
		i++;
	}
}
