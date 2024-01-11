/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:52:46 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:52:47 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_malloc(t_philo **a)
{
	if (!a)
		return (0);
	if (!a[0])
	{
		free(a);
		return (0);
	}
	if (a && a[0] && (!a[0]->death || !a[0]->threads
			|| !a[0]->muteces || !a[0]->forks))
	{
		printf("error allocating memory\n");
		if (a[0]->death)
			free(a[0]->death);
		if (a[0]->threads)
			free(a[0]->threads);
		if (a[0]->forks)
			free(a[0]->forks);
		if (a[0]->muteces)
			pthread_mutex_destroy(a[0]->muteces);
		free(a[0]);
		free(a);
		return (0);
	}
	else
		return (1);
}
