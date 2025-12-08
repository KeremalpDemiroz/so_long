#include "so_long.h"

void	get_position(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map.y_max)
	{
		x = 0;
		while (x < data->map.x_max)
		{
			if (data->map.grid[y][x] == 'P')
			{
				data->p_x = x;
				data->p_y = y;
			}
			else if (data->map.grid[y][x] == 'E')
			{
				data->e_x = x;
				data->e_y = y;
			}
			x++;
		}
		y++;
	}
}

void	to_the_grid(t_data *data)
{
	t_list	*tmp;
	int		y;

	y = 0;
	tmp = data->list;
	data->map.y_max = count_node(data);
	data->map.grid = malloc(sizeof(char *) * (data->map.y_max + 1));
	if (!data->map.grid)
		print_error("Map file can not be read", data);
	while (tmp)
	{
		data->map.grid[y] = tmp->line;
		tmp->line = NULL;
		y++;
		tmp = tmp->next;
	}
	data->map.grid[y] = NULL;
	free_node(&data->list);
}

void	check_features(t_data *data)
{
	if (data->map.count_c == 0)
		print_error("No collectible items(C) found on the map", data);
	if (data->map.count_e != 1)
	{
		if (data->map.count_e == 0)
			print_error("No exit(E) found on the map", data);
		else
			print_error("Map contains multiple exits", data);
	}
	if (data->map.count_p != 1)
	{
		if (data->map.count_p == 0)
			print_error("No player(P) found on the map", data);
		else
			print_error("Map contains multiple players", data);
	}
}

char	**create_map_copy(t_data *data)
{
	char	**map_copy;
	int		y;

	y = 0;
	if (!data->map.grid)
		print_error("Map file can not be read", data);
	map_copy = malloc(sizeof(char *) * (data->map.y_max + 1));
	while (y < data->map.y_max)
	{
		map_copy[y] = ft_strdup(data->map.grid[y]);
		if (!map_copy[y])
		{
			all_free(map_copy);
			print_error("Map file can not be read", data);
		}
		y++;
	}
	map_copy[y] = NULL;
	return (map_copy);
}

void	count_features(char *line, t_data *data, int *flag)
{
	int	i;

	i = 0;
	while (line[i] == '1' || line[i] == '0' || line[i] == 'P'
		|| line[i] == 'C' || line[i] == 'E')
	{
		if (line[i] == 'P')
			data->map.count_p++;
		else if (line[i] == 'C')
			data->map.count_c++;
		else if (line[i] == 'E')
			data->map.count_e++;
		i++;
	}
	if (line[i] == '\0' || line[i] == '\n')
		return ;
	else
		*flag = 0;
}
