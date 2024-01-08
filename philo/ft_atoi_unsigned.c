unsigned int	ft_atoi_unsigned(const char *str)
{
	int				i;
	unsigned int	result;

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
