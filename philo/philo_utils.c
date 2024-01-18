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

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc != 5 && argc != 6)
		return (print_error());
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < 48 || argv[i][j] > 57)
			{
				print_error();
				return (0);
			}
			j++;
		}
		if (((i == 1 || i == 5) && ft_atoi_unsigned(argv[i]) == 0)
			|| check_overflow(argv[i]))
			return (print_error());
		i++;
	}
	return (1);
}

int	print_error(void)
{
	printf("invalid input\n");
	return (0);
}

void	destroy_muteces(t_philo **arr, unsigned int n)
{
	unsigned int	i;

	pthread_mutex_destroy(arr[0]->death_mutex);
	free(arr[0]->death_mutex);
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&arr[0]->muteces[i]);
		pthread_mutex_destroy(&arr[0]->time_mutex[i]);
		i++;
	}
	free(arr[0]->muteces);
	free(arr[0]->time_mutex);
}

void	free_philo_arr(t_philo **arr, unsigned int n)
{
	unsigned int	i;

	if (arr[0]->threads)
		free(arr[0]->threads);
	if (arr[0]->death)
		free(arr[0]->death);
	if (arr[0]->forks)
		free(arr[0]->forks);
	i = 0;
	while (i < n)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

int	free_philo(t_philo **arr, int exit, unsigned int n)
{
	destroy_muteces(arr, n);
	if (arr)
		free_philo_arr(arr, n);
	if (exit == 2)
		printf("error creating threads\n");
	if (exit == 3)
		printf("error joining threads\n");
	if (exit == 4)
		printf("error allocating memory\n");
	if (exit == 5)
		printf("error creating mutex\n");
	return (exit);
}
