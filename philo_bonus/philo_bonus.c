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

t_philo	*init_philo_values(int argc, char **argv, t_philo *p, sem_t *done, sem_t *death)
{
	if (p)
	{
		p->done = done;
		p->death = death;
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

t_philo	*init_philo_ptrs(unsigned int n)
{
	int				*pids;
	t_philo			*p;
	unsigned int	i;

	p = malloc(sizeof(t_philo));
	pids = malloc(sizeof(int) * (n + 1));
	if (check_malloc(p, pids) == 0)
		return (0);
	init_pids(pids, n);
	i = 0;
	while (i < n)
	{
		p->pids = pids;
		i++;
	}
	return (p);
}

void	init_processes(t_philo *p, int n, sem_t *done, sem_t *death)
{
	int		i;

	i = 0;
	p->timestamp_start = sys_timestamp();
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
	if (p->must_eat > 0)
	{
		i = 0;
		while (i < p->n)
		{
			sem_wait(done);
			i++;
		}
		sem_post(death);
	}
	i = 0;
	while (i < p->n)
		waitpid(p->pids[i++], 0, 0);
}

int	main(int argc, char **argv)
{
	t_philo	*p;
	sem_t	*done;		
	sem_t	*death;

	sem_unlink("/forks");
	sem_unlink("/death");
	sem_unlink("/print");
	sem_unlink("/done");
	if (!check_input(argc, argv))
		return (0);
	done = sem_open("/done", O_CREAT, 0666, 0);
	death = sem_open("/death", O_CREAT, 0666, 0);
	if (sem_open("/forks", O_CREAT, 0666,
			ft_atoi_unsigned(argv[1])) == SEM_FAILED
		|| sem_open("/print", O_CREAT, 0666, 1) == SEM_FAILED || done == SEM_FAILED)
		free_philo(0, 1);
	p = init_philo_ptrs(ft_atoi_unsigned(argv[1]));
	if (!p)
		return (free_philo(p, 3));
	p = init_philo_values(argc, argv, p, done, death);
	init_processes(p, ft_atoi_unsigned(argv[1]), done, death);
	return (free_philo(p, 0));
}
