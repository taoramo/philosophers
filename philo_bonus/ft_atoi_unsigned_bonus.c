/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:52:09 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:52:11 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned int	ft_atoi_unsigned(const char *str)
{
	int					i;
	unsigned int		result;

	if (!str)
		return (0);
	result = 0;
	i = 0;
	while (str[i] != 0 && str[i] > 47 && str[i] < 58)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (result);
}

int	check_overflow(const char *str)
{
	int						i;
	unsigned long int		result;

	if (!str)
		return (0);
	result = 0;
	i = 0;
	while (str[i] != 0 && str[i] > 47 && str[i] < 58)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	if (result > 4294967295)
		return (1);
	else
		return (0);
}

char	*ft_utoa(unsigned int nb, char *dst)
{
	int		n;
	int		j;
	char	nbr[16];

	n = 1;
	nbr[0] = (nb % 10) + 97;
	while (nb / 10 != 0)
	{
		nb = nb / 10;
		nbr[n] = (nb % 10) + 97;
		n++;
	}
	n--;
	dst[0] = '/';
	j = 1;
	while (n >= 0)
	{
		dst[j] = nbr[n];
		n--;
		j++;
	}
	dst[j] = 0;
	return (dst);
}
