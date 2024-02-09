/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:53:56 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:53:57 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_error(void)
{
	printf("Invalid input\n");
	return (0);
}

unsigned long int	sys_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(unsigned long milliseconds)
{
	unsigned long	start;

	start = sys_timestamp();
	while ((sys_timestamp() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	init_pids(int *pids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pids[i] = 1;
		i++;
	}
}

int	free_philo(t_philo *p, int exitnum)
{
	if (exitnum == 1)
		printf("error creating semaphores\n");
	if (exitnum == 2)
		printf("error forking\n");
	sem_close(p->forks);
	sem_unlink("/forks");
	sem_close(p->death);
	sem_unlink("/death");
	sem_close(p->print);
	sem_unlink("/print");
	sem_close(p->done);
	sem_unlink("/done");
	if (!p)
		exit(exitnum);
	free(p->pids);
	free(p);
	exit(exitnum);
	return (0);
}
