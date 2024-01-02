/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:52:46 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:52:47 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(void)
{
	printf("Invalid input\n");
	return (0);
}

unsigned long int	timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(unsigned long milliseconds)
{
	unsigned long	start;

	start = timestamp();
	while ((timestamp() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	free_philo(t_philo **arr, int exit, unsigned int n)
{
	unsigned int	i;

	i = 0;
	free(arr[0]->threads);
	free(arr[0]->muteces);
	free(arr[0]->death);
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	if (exit == 2)
		printf("error creating threads\n");
	if (exit == 3)
		printf("error joining threads\n");
	return (exit);
}
