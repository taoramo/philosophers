/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:52:36 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:52:36 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_finished(t_philo **arr)
{
	pthread_mutex_lock(arr[0]->death_mutex);
	if (*arr[0]->death == 1)
	{
		pthread_mutex_unlock(arr[0]->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(arr[0]->death_mutex);
	return (0);
}

int	check_death(t_philo **arr)
{
	unsigned int	i;
	int				result;

	i = 0;
	result = 0;
	while (i < arr[0]->n)
	{
		pthread_mutex_lock(&arr[i]->time_mutex[i]);
		if (timestamp(arr[0]) - arr[i]->timestamp_eat > arr[i]->time_die)
		{
			pthread_mutex_unlock(&arr[i]->time_mutex[i]);
			pthread_mutex_lock(arr[0]->death_mutex);
			*arr[0]->death = 1;
			pthread_mutex_unlock(arr[0]->death_mutex);
			printf("%lu %u has died\n", timestamp(arr[0]), i + 1);
			result = 1;
			break ;
		}
		pthread_mutex_unlock(&arr[i]->time_mutex[i]);
		i++;
	}
	return (result);
}

void	*philo_monitor(void *arg)
{
	t_philo	**arr;

	arr = (t_philo **)arg;
	ft_usleep(arr[0]->time_die / 2);
	while (1)
	{
		if (is_finished(arr))
			return (0);
		if (check_death(arr))
			return (0);
		usleep(2000);
	}
}
