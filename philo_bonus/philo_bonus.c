/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:53:29 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:53:30 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*init_philo_values(int argc, char **argv, t_philo *p)
{
	if (p)
	{
		p->n = ft_atoi_unsigned(argv[1]);
		p->time_die = ft_atoi_unsigned(argv[2]);
		p->time_eat = ft_atoi_unsigned(argv[3]);
		p->time_sleep = ft_atoi_unsigned(argv[4]);
		if (argc == 5)
			p->must_eat = -1;
		if (argc == 6)
			p->must_eat = ft_atoi_unsigned(argv[5]);
		p->timestamp_eat = 0;
		p->i = -1;
	}
	return (p);
}

int	check_malloc(t_philo *a, int *p)
{
	if (!a || !p)
	{
		printf("Error allocating memory\n");
		if (a)
			free(a);
		if (p)
			free(p);
		return (0);
	}
	else
		return (1);
}

t_philo	*init_philo_ptrs(unsigned int n, int argc, char **argv)
{
	int				*pids;
	t_philo			*p;
	unsigned int	i;

	if (!check_input(argc, argv))
		return (0);
	p = malloc(sizeof(t_philo));
	pids = malloc(sizeof(int) * (n + 1));
	init_pids(pids, n);
	if (check_malloc(p, pids) == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		p->pids = pids;
		i++;
	}
	return (p);
}

void	init_processes(t_philo *p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		p->pids[i] = fork();
		if (p->pids[i] == -1)
			free_philo(p, 2);
		if (p->pids[i] == 0)
		{
			philosopher(p);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < p->n)
		waitpid(p->pids[i++], 0, 0);
}

int	main(int argc, char **argv)
{
	t_philo			*p;
	pthread_t		monitor;

	sem_unlink("/forks");
	sem_unlink("/death");
	if (sem_open("/forks", O_CREAT, 0666,
			ft_atoi_unsigned(argv[1])) == SEM_FAILED
		|| sem_open("/death", O_CREAT, 0666, 0) == SEM_FAILED)
		free_philo(0, 1);
	p = init_philo_ptrs(ft_atoi_unsigned(argv[1]), argc, argv);
	if (!p)
		return (free_philo(p, 3));
	p = init_philo_values(argc, argv, p);
	if (pthread_create(&monitor, 0, &philo_monitor, p) != 0)
		free_philo(p, 4);
	init_processes(p, ft_atoi_unsigned(argv[1]));
	return (free_philo(p, 0));
}
