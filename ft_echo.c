int	ft_echo(char **args, char **env, char *ret)
{
	int			i;

	i = 0;
	if (!ft_strcmp(args[0], "-n"))
		i++;
	while (args[i])
		ft_printf("%s", args[i++]);
	if (ft_strcmp(args[0], "-n"))
		ft_printf("\n");
	return (0);
}