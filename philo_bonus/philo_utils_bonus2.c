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

void	*ft_death(void *arg)
{
	t_philo	*p;
	sem_t	*death;

	p = (t_philo *)arg;
	death = sem_open("/death", 0);
	if (death == SEM_FAILED)
		printf("Error opening death semaphore\n");
	sem_wait(death);
	free(p->pids);
	free(p);
	sem_post(death);
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
		if ((i == 1 || i == 5) && ft_atoi_unsigned(argv[i]) == 0)
			return (print_error());
		i++;
	}
	return (1);
}
