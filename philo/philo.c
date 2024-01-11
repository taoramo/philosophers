/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:53:00 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:53:01 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	**init_philo_values(int argc, char **argv, t_philo **arr)
{
	unsigned int	i;

	i = 0;
	while (i < ft_atoi_unsigned(argv[1]) && arr)
	{
		arr[i]->n = ft_atoi_unsigned(argv[1]);
		arr[i]->time_die = ft_atoi_unsigned(argv[2]);
		arr[i]->time_eat = ft_atoi_unsigned(argv[3]);
		arr[i]->time_sleep = ft_atoi_unsigned(argv[4]);
		if (argc == 5)
			arr[i]->must_eat = -1;
		if (argc == 6)
			arr[i]->must_eat = ft_atoi_unsigned(argv[5]);
		arr[i]->i = i;
		arr[0]->forks[i] = 0;
		i++;
	}
	return (arr);
}

int	init_muteces(t_philo **arr, unsigned int n)
{
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*time_mutex;
	unsigned int	i;

	death_mutex = malloc(sizeof(pthread_mutex_t *));
	time_mutex = malloc(sizeof(pthread_mutex_t) * n);
	if (!death_mutex || !time_mutex)
		return (free_philo(arr, 4, n));
	if (pthread_mutex_init(death_mutex, 0) != 0)
		return (free_philo(arr, 5, n));
	i = 0;
	while (i < n)
	{
		arr[i]->death_mutex = death_mutex;
		arr[i]->time_mutex = time_mutex;
		if (pthread_mutex_init(&time_mutex[i], 0) != 0
			|| pthread_mutex_init(&arr[i]->muteces[i], 0) != 0)
			return (free_philo(arr, 5, n));
		i++;
	}
	return (0);
}

t_philo	**init_philo_ptrs(unsigned int n)
{
	t_philo			**arr;
	unsigned int	i;

	arr = malloc(sizeof(t_philo *) * n);
	arr[0] = malloc(sizeof(t_philo));
	arr[0]->death = (int *)malloc(sizeof(int *));
	arr[0]->threads = malloc(sizeof(pthread_t) * (n + 1));
	arr[0]->muteces = malloc(sizeof(pthread_mutex_t) * n);
	arr[0]->forks = malloc(sizeof(int) * n);
	*arr[0]->death = 0;
	if (check_malloc(arr) == 0)
		return (0);
	i = 1;
	while (i < n)
	{
		arr[i] = malloc(sizeof(t_philo));
		arr[i]->death = arr[0]->death;
		arr[i]->threads = arr[0]->threads;
		arr[i]->muteces = arr[0]->muteces;
		arr[i]->forks = arr[0]->forks;
		i++;
	}
	init_muteces(arr, n);
	return (arr);
}

int	manage_threads(t_philo **arr, char **argv)
{
	unsigned int	i;

	i = 0;
	set_start_time(arr);
	while (i < arr[0]->n)
	{
		if (pthread_create(&arr[0]->threads[i], 0, &philosopher, arr[i]) != 0)
			return (free_philo(arr, 2, ft_atoi_unsigned(argv[1])));
		i++;
	}
	if (pthread_create(&arr[0]->threads[i], 0, &philo_monitor, arr) != 0)
		return (free_philo(arr, 2, ft_atoi_unsigned(argv[1])));
	i = 0;
	while (i < arr[0]->n)
	{
		if (pthread_join(arr[0]->threads[i], 0) != 0)
			return (free_philo(arr, 3, ft_atoi_unsigned(argv[1])));
		i++;
	}
	pthread_mutex_lock(arr[0]->death_mutex);
	*arr[0]->death = 1;
	pthread_mutex_unlock(arr[0]->death_mutex);
	if (pthread_join(arr[0]->threads[arr[0]->n], 0) != 0)
		return (free_philo(arr, 3, ft_atoi_unsigned(argv[1])));
	return (free_philo(arr, 0, ft_atoi_unsigned(argv[1])));
}

int	main(int argc, char **argv)
{
	t_philo			**arr;

	if (!check_input(argc, argv))
		return (0);
	arr = init_philo_ptrs(ft_atoi_unsigned(argv[1]));
	if (!arr)
		return (free_philo(arr, 1, ft_atoi_unsigned(argv[1])));
	arr = init_philo_values(argc, argv, arr);
	return (manage_threads(arr, argv));
}
