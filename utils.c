int	ft_strlenbuf(char **buf)
{
	int	i;

	i = 0;
	while (buf[i])
		i++;
	return (i);
}