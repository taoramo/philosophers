#include "philo.h"

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

t_philo	**init_philo_values(int argc, char **argv, t_philo **arr)
{
	unsigned int	i;

	i = 0;
	while (i < ft_atoi_unsigned(argv[1]) && arr)
	{
		arr[i]->n = ft_atoi_unsigned(argv[1]);
		arr[i]->time_die = ft_atoi_unsigned(argv[2]);
		arr[i]->time_eat = ft_atoi_unsigned(argv[3]);
		arr[i]->time_sleep = ft_atoi_unsigned(argv[4]);
		if (argc == 5)
			arr[i]->must_eat = -1;
		if (argc == 6)
			arr[i]->must_eat = ft_atoi_unsigned(argv[5]);
		arr[i]->i = i;
		i++;
	}
	return (arr);
}

int	check_malloc(t_philo **a, int *d, pthread_t *t, pthread_mutex_t *m)
{
	if (!a || !d || !t || !m)
	{
		printf("Error allocating memory\n");
		if (a)
			free(a);
		if (d)
			free(d);
		if (t)
			free(t);
		if (m)
			free(m);
		return (0);
	}
	else
		return (1);
}

t_philo	**init_philo_ptrs(unsigned int n, int argc, char **argv)
{
	int				*death;
	pthread_t		*threads;
	pthread_mutex_t	*muteces;
	t_philo			**arr;
	unsigned int	i;

	if (!check_input(argc, argv))
		return (0);
	arr = malloc(sizeof(t_philo *) * n);
	death = (int *)malloc(sizeof(int *));
	threads = malloc(sizeof(pthread_t) * (n + 1));
	muteces = malloc(sizeof(pthread_mutex_t) * n);
	*death = 0;
	if (check_malloc(arr, death, threads, muteces) == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		arr[i] = malloc(sizeof(t_philo));
		arr[i]->death = death;
		arr[i]->threads = threads;
		arr[i]->muteces = muteces;
		i++;
	}
	return (arr);
}

int	main(int argc, char **argv)
{
	t_philo			**arr;
	int				i;

	arr = init_philo_ptrs(ft_atoi_unsigned(argv[1]), argc, argv);
	if (!arr)
		return (free_philo(arr, 1, ft_atoi_unsigned(argv[1])));
	arr = init_philo_values(argc, argv, arr);
	i = 0;
	while (i < arr[0]->n)
	{
		if (pthread_create(&arr[0]->threads[i], 0, &philosopher, arr[i]) != 0
			|| pthread_mutex_init(&arr[0]->muteces[i], 0) != 0)
			return (free_philo(arr, 2, ft_atoi_unsigned(argv[1])));
		i++;
	}
	if (pthread_create(&arr[0]->threads[i], 0, &philo_monitor, arr) != 0)
		return (free_philo(arr, 2, ft_atoi_unsigned(argv[1])));
	while (i)
	{
		if (pthread_join(arr[0]->threads[i], 0) != 0)
			return (free_philo(arr, 3, ft_atoi_unsigned(argv[1])));
		i--;
	}
	return (free_philo(arr, 0, ft_atoi_unsigned(argv[1])));
}
