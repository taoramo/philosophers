/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toramo <toramo.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 10:53:39 by toramo            #+#    #+#             */
/*   Updated: 2024/01/02 10:54:47 by toramo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo {
	unsigned int		time_die;
	unsigned int		time_sleep;
	unsigned int		time_eat;
	unsigned long int	timestamp_eat;
	int					must_eat;
	int					n;
	int					i;
	int					*pids;
	sem_t				*forks;
}	t_philo;
unsigned int		ft_atoi_unsigned(const char *str);
int					free_philo(t_philo *arr, int exit);
void				*philosopher(void *arg);
void				*philo_monitor(void *arg);
unsigned long int	timestamp(void);
int					ft_usleep(unsigned long milliseconds);
void				eat(t_philo *p);
void				philo_sleep(t_philo *p);
void				think(t_philo *p);
int					print_error(void);
void				init_pids(int *pids, int n);
int					check_input(int argc, char **argv);
void				*ft_death(void *arg);
#endif
