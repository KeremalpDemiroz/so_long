#include "so_long.h"

void	all_free(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	print_error(char *err_msg, t_data *data)
{
	clean_data(data);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}
