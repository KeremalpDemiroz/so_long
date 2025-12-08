#include "so_long.h"

void	read_map(t_data *data)
{
	char	*line;
	int		flag;

	flag = 1;
	data->map_fd = open(data->av[1], O_RDONLY);
	if (data->map_fd < 0)
		print_error("Map file can not be read", data);
	while (1)
	{
		line = get_next_line(data->map_fd);
		if (!line)
			break ;
		add_back(&data->list, new_node(line, ft_strlen(line), data));
		count_features(line, data, &flag);
	}
	if (!data->list)
		print_error("Map file can not be read", data);
	if (!flag)
		print_error("Invalid character on map", data);
	close(data->map_fd);
	data->map_fd = -1;
}

void	check_map_name(t_data *data)
{
	char	*ext;
	int		i;
	int		j;

	i = 0;
	ext = ".ber";
	if (!data->av[1] || ft_strlen(data->av[1]) < 4)
		print_error("File name doesn't exist", data);
	while (data->av[1][i])
	{
		j = 0;
		while (data->av[1][i + j] && ext[j] == data->av[1][i + j])
			j++;
		if (ext[j] == '\0' && !data->av[1][i + j])
			return ;
		i++;
	}
	print_error("File extension is not valid", data);
}

void	is_it_rectanguler(t_data *data)
{
	t_list	*tmp;
	int		x;

	tmp = data->list;
	x = tmp->len;
	while (tmp->next)
	{
		if (tmp->next->len != x)
			print_error("Map is not rectanguler", data);
		x = tmp->len;
		tmp = tmp->next;
	}
	data->map.x_max = x;
}

void	is_it_surrounded(t_data *data)
{
	char	*check;
	int		i;

	i = 0;
	while (i < data->map.y_max)
	{
		check = ft_strtrim(data->map.grid[i], "1\n");
		if ((i == 0 || i == data->map.y_max -1) && check[0])
		{
			free(check);
			print_error("Map is not surrounded by walls", data);
		}
		else if ((int)ft_strlen(check) > data->map.x_max -3)
		{
			free(check);
			print_error("Map is not surrounded by walls", data);
		}
		free(check);
		i++;
	}
}

void	is_it_playable(t_data *data)
{
	char	**map_copy;
	int		x;
	int		y;

	y = 0;
	map_copy = create_map_copy(data);
	flood_fill(map_copy, data->p_x, data->p_y, data);
	while (map_copy[y])
	{
		x = 0;
		while (map_copy[y][x])
		{
			if (map_copy[y][x] != '1' && map_copy[y][x] != '0'
				&& map_copy[y][x] != '\n')
			{
				all_free(map_copy);
				print_error("Map is can not playable", data);
			}
			x++;
		}
		y++;
	}
	all_free(map_copy);
}
