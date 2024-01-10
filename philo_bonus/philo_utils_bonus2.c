/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:54:04 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:54:05 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	open_semaphores(t_philo *p)
{
	sem_t	*forks;
	sem_t	*death;
	char	name[32];

	ft_strlcpy(name, "/time", 6);
	ft_utoa(p->i, &name[5]);
	sem_unlink(name);
	p->time = sem_open(name, O_CREAT, 0666, 1);
	if (p->time == SEM_FAILED)
		free_philo(p, 1);
	forks = sem_open("/forks", 0);
	death = sem_open("/death", 0);
	if (forks == SEM_FAILED || death == SEM_FAILED || p->time == SEM_FAILED)
		free_philo(p, 1);
	p->forks = forks;
	p->death = death;
}

void	*ft_death(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	sem_wait(p->death);
	sem_post(p->death);
	free(p->pids);
	free(p);
	exit(0);
	return (0);
}

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
				return (0);
			j++;
		}
		if (((i == 1 || i == 5) && ft_atoi_unsigned(argv[i]) == 0)
			|| check_overflow(argv[i]))
			return (print_error());
		i++;
	}
	return (1);
}

unsigned long int	timestamp(t_philo *p)
{
	return (sys_timestamp() - p->timestamp_start);
}
