/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:53:29 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:53:30 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	int	n;

	n = 0;
	if (str[0] != 0)
	{
		while (str[n] != 0)
		{
			n++;
		}
	}
	return (n);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int		i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != 0 && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
		return (ft_strlen(src));
	}
	else
	{
		return (ft_strlen(src));
	}
}
