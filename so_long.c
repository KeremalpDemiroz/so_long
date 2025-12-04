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

void	free_node(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		if ((*list)->line)
			free((*list)->line);
		free(*list);
		*list = temp;
	}
	*list = NULL;
}

void	clean_game_data(t_game *game)
{
	if (game->mlx)
		free(game->mlx);
	if (game->win)
		free(game->win);
}

void	clean_map_data(t_map *map)
{
	if (map->grid)
		all_free(map->grid);
}

void	clean_image_data(t_image *img)
{
	if (img->coin)
		free(img->coin);
	if (img->e_o)
		free(img->e_o);
	if (img->e_c)
		free(img->e_c);
	if (img->p_f)
		free(img->p_f);
	if (img->p_b)
		free(img->p_b);
	if (img->p_l)
		free(img->p_l);
	if (img->p_r)
		free(img->p_r);
	if (img->wall)
		free(img->wall);
	if (img->floor)
		free(img->floor);
}

void	clean_data(t_data *data)
{
	if (data->list)
		free_node(&data->list);
	if (data->map_fd != -1)
		close(data->map_fd);
	clean_game_data(&data->game);
	clean_map_data(&data->map);
	clean_image_data(&data->img);
}

void	print_error(char *err_msg, t_data *data)
{
	clean_data(data);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}

void	add_back(t_list **list, t_list *new)
{
	t_list	*temp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	count_node(t_data *data)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = data->list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_list	*new_node(char *line, int len, t_data *data)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		print_error("Map file can not be read", data);
	node->line = line;
	node->len = len;
	node->next = NULL;
	return (node);
}

void	start_game_data(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->height = 0;
	game->width = 0;
}

void	start_map_data(t_map *map)
{
	map->grid = NULL;
	map->count_c = 0;
	map->count_e = 0;
	map->count_p = 0;
}

void	start_image_data(t_image *img)
{
	img->p_f = NULL;
	img->p_b = NULL;
	img->p_r = NULL;
	img->p_l = NULL;
	img->e_c = NULL;
	img->e_o = NULL;
	img->coin = NULL;
	img->floor = NULL;
	img->wall = NULL;
}

void	start_data(t_data *data, char **av, int ac)
{
	data->av = av;
	data->ac = ac;
	data->list = NULL;
	data->map_fd = -1;
	data->moves_count = 0;
	start_game_data(&(data->game));
	start_map_data(&(data->map));
	start_image_data(&(data->img));
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

void	read_map(t_data *data)
{
	char	*line;
	char	*tmp;
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
		else if (ft_strlen(check) > data->map.x_max -3)
		{
			free(check);
			print_error("Map is not surrounded by walls", data);
		}
		free(check);
		i++;
	}
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

void	flood_fill(char	**map_copy, int x, int y, t_data *data)
{
	if (x <= 0 || y <= 0 || x >= data->map.x_max || y >= data->map.y_max)
		return ;
	if (map_copy[y][x] == '1')
		return ;
	map_copy[y][x] = '1';
	flood_fill(map_copy, x + 1, y, data);
	flood_fill(map_copy, x - 1, y, data);
	flood_fill(map_copy, x, y + 1, data);
	flood_fill(map_copy, x, y - 1, data);
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

void	check_map(t_data *data)
{
	if (data->ac > 2)
		print_error("2 or more maps in arguments", data);
	check_map_name(data);
	read_map(data);
	is_it_rectanguler(data);
	to_the_grid(data);
	is_it_surrounded(data);
	check_features(data);
	get_position(data);
	is_it_playable(data);
	data->game.height = (data->map.y_max) * 64;
	data->game.width = (data->map.x_max - 1) * 64;
}

void	reinitialize_image(t_data *data)
{
	data->img.floor = NULL;
	data->img.wall = NULL;
	data->img.coin = NULL;
	data->img.e_o = NULL;
	data->img.e_c = NULL;
	data->img.p_f = NULL;
	data->img.p_b = NULL;
	data->img.p_r = NULL;
	data->img.p_l = NULL;
}

void	destroy_images(t_data *data)
{
	if (data->img.p_f)
		mlx_destroy_image(data->game.mlx, data->img.p_f);
	if (data->img.p_b)
		mlx_destroy_image(data->game.mlx, data->img.p_b);
	if (data->img.p_r)
		mlx_destroy_image(data->game.mlx, data->img.p_r);
	if (data->img.p_l)
		mlx_destroy_image(data->game.mlx, data->img.p_l);
	if (data->img.e_o)
		mlx_destroy_image(data->game.mlx, data->img.e_o);
	if (data->img.e_c)
		mlx_destroy_image(data->game.mlx, data->img.e_c);
	if (data->img.floor)
		mlx_destroy_image(data->game.mlx, data->img.floor);
	if (data->img.wall)
		mlx_destroy_image(data->game.mlx, data->img.wall);
	if (data->img.coin)
		mlx_destroy_image(data->game.mlx, data->img.coin);
	reinitialize_image(data);
}

void	clean_exit(t_data *data, char *err_msg)
{
	if (data->game.win)
		mlx_destroy_window(data->game.mlx, data->game.win);
	destroy_images(data);
	if (data->game.mlx)
		mlx_destroy_display(data->game.mlx);
	data->game.win = NULL;
	data->game.win = NULL;
	if (err_msg)
		print_error(err_msg, data);
	else
	{
		clean_data(data);
		exit (0);
	}
}

void	*swap_img_ptr(void	*img_ptr, void	**img_id, t_data *data)
{
	if (!img_ptr)
		clean_exit(data, "Image file can not be read");
	*img_id = img_ptr;
	return (NULL);
}

void	get_img_ptr(t_data *data)
{
	void	*img_ptr;
	int		height;
	int		width;

	height = 64;
	width = 64;
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, P_F, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.p_f, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, P_B, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.p_b, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, P_F, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.p_r, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, P_F, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.p_l, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, FLOOR, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.floor, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, COIN, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.coin, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, WALL, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.wall, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, E_C, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.e_c, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, E_O, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.e_o, data);
}

void	print_image_to_window(t_data *data, int x, int y)
{
	if (data->map.grid[y][x] == '1')
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.wall, x * 64, y * 64);
	if (data->map.grid[y][x] == '0')
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.floor, x * 64, y * 64);
	if (data->map.grid[y][x] == 'E')
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.e_c, x * 64, y * 64);
	if (data->map.grid[y][x] == 'P')
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.p_f, x * 64, y * 64);
	if (data->map.grid[y][x] == 'C')
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.coin, x * 64, y * 64);
}

int	render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	mlx_string_put(data->game.mlx, data->game.win, 64, 64, 0xffff, "number");
	while (y < data->map.y_max)
	{
		x = 0;
		while (x < data->map.x_max)
		{
			print_image_to_window(data, x, y);
			x++;
		}
		y++;
	}
	mlx_string_put(data->game.mlx, data->game.win, 64, 64, 0x464646, "number");
	return (0);
}

void	update_map(t_data *data, int old_x, int old_y)
{
	if (data->map.grid[data->p_y][data->p_x] != '1')
	{
		data->moves_count++;
		data->map.grid[old_y][old_x] = '0';
		if (old_y == data->e_y && old_x == data->e_x)
			data->map.grid[old_y][old_x] = 'E';
		if (data->map.grid[data->p_y][data->p_x] == 'C')
		{
			data->map.count_c--;
			data->map.grid[data->p_y][data->p_x] = 'P';
		}
		else if (data->map.grid[data->p_y][data->p_x] == 'E')
		{
			ft_printf("Moves count: %d\n", data->moves_count);
			if (!data->map.count_c)
				clean_exit(data, NULL);
			data->map.grid[data->p_y][data->p_x] = 'P';
		}
		else
			data->map.grid[data->p_y][data->p_x] = 'P';
		printf("Moves count: %d\n", data->moves_count);
		return ;
	}
	data->p_x = old_x;
	data->p_y = old_y;
}

void	player_move(t_data *data, int keycode)
{
	if (keycode == W)
		data->p_y--;
	else if (keycode == S)
		data->p_y++;
	else if (keycode == A)
		data->p_x--;
	else if (keycode == D)
		data->p_x++;
}

int	key_handler(int keycode, void *param)
{
	t_data	*data;
	int		old_x;
	int		old_y;

	data = param;
	old_x = data->p_x;
	old_y = data->p_y;
	if (keycode == 65307)
		clean_exit(data, NULL);
	if (keycode == W || keycode == S || keycode == A || keycode == D)
		player_move(data, keycode);
	update_map(data, old_x, old_y);
	render(data);
	return (0);
}

int	close_window(void	*param)
{
	clean_exit(param, NULL);
}

void	check_screen_size(t_data *data)
{
	int	screen_y;
	int	screen_x;

	mlx_get_screen_size(data->game.mlx, &screen_x, &screen_y);
	if (screen_x < data->game.width || screen_y < data->game.height)
		clean_exit(data, "Map size is bigger than display screen");
}

int	main(int ac, char **av)
{
	t_data	data;

	start_data(&data, av, ac);
	check_map(&data);
	data.game.mlx = mlx_init();
	check_screen_size(&data);
	get_img_ptr(&data);
	data.game.win = mlx_new_window(data.game.mlx, data.game.width,
			data.game.height, "so_long");
	mlx_hook(data.game.win, 2, 1L << 0, key_handler, &data);
	mlx_hook(data.game.win, 17, 0, close_window, &data);
	mlx_expose_hook(data.game.win, render, &data);
	render(&data);
	mlx_loop(data.game.mlx);
}
