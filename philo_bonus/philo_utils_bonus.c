#include "philo_bonus.h"

int	print_error(void)
{
	printf("Invalid input\n");
	return (0);
}

unsigned long int	timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(unsigned long milliseconds)
{
	unsigned long	start;

	start = timestamp();
	while ((timestamp() - start) < milliseconds)
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
	sem_t	*forks;
	sem_t	*death;

	if (exitnum == 1)
		printf("error creating semaphores\n");
	if (exitnum == 2)
		printf("error forking\n");
	forks = sem_open("/forks", 0);
	death = sem_open("/death", 0);
	sem_close(forks);
	sem_unlink("/forks");
	sem_close(death);
	sem_unlink("/death");
	if (!p)
		exit(exitnum);
	free(p->pids);
	free(p);
	exit(exitnum);
	return (0);
}
