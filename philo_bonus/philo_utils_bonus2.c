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
	sem_t	*print;
	char	name[32];

	ft_strlcpy(name, "/time", 6);
	ft_utoa(p->i, &name[5]);
	sem_unlink(name);
	p->time = sem_open(name, O_CREAT, 0666, 1);
	if (p->time == SEM_FAILED)
		free_philo(p, 1);
	forks = sem_open("/forks", 0);
	death = sem_open("/death", 0);
	print = sem_open("/print", 0);
	if (forks == SEM_FAILED || death == SEM_FAILED || p->time == SEM_FAILED
		|| print == SEM_FAILED)
		free_philo(p, 1);
	p->forks = forks;
	p->death = death;
	p->print = print;
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

void	philo_print(t_philo *p, char *action)
{
	sem_wait(p->print);
	printf("%lu %u %s\n", timestamp(p), p->i + 1, action);
	sem_post(p->print);
}

unsigned long int	timestamp(t_philo *p)
{
	return (sys_timestamp() - p->timestamp_start);
}
