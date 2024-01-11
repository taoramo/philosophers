/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:52:17 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:52:21 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>

typedef struct s_philo {
	unsigned int		time_die;
	unsigned int		time_sleep;
	unsigned int		time_eat;
	unsigned long int	timestamp_eat;
	unsigned long int	timestamp_start;
	int					must_eat;
	int					*death;
	unsigned int		n;
	int					i;
	pthread_mutex_t		*muteces;
	pthread_t			*threads;
	int					*forks;
	pthread_mutex_t		*death_mutex;
	pthread_mutex_t		*time_mutex;
}	t_philo;
unsigned int		ft_atoi_unsigned(const char *str);
int					free_philo(t_philo **arr, int exit, unsigned int n);
void				*philosopher(void *arg);
void				*philo_monitor(void *arg);
unsigned long int	timestamp(t_philo *p);
unsigned long int	sys_timestamp(void);
int					ft_usleep(unsigned long milliseconds);
void				eat(t_philo *p);
void				philo_sleep(t_philo *p);
void				think(t_philo *p);
int					print_error(void);
int					is_dead(t_philo *p);
void				set_start_time(t_philo **arr);
int					check_malloc(t_philo **arr);
int					check_input(int argc, char **argv);
int					check_overflow(const char *str);
#endif
