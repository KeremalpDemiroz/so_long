#include "minilibx-linux/mlx.h"
#include "so_long.h"
#include "sources/libft.h"
#include <stdio.h>
#include <fcntl.h>


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
	if (img->exit)
		free(img->exit);
	if (img->player)
		free(img->player);
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
void	start_game_data(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
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
	img->player = NULL;
	img->coin = NULL;
	img->exit = NULL;
	img->floor = NULL;
	img->wall = NULL;
}


void	start_data(t_data *data, char **av, int ac)
{
	data->av = av;
	data->ac = ac;
	data->list = NULL;
	data->map_fd = -1;
	start_game_data(&(data->game));
	start_map_data(&(data->map));
	start_image_data(&(data->img));
}

void	check_map_name(t_data *data)
{
	int	i;
	int	j;
	char	*ext;

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
			print_error("Map is not rectanguler",data);
		x =  tmp->len;
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
		print_error("Map file can not be read",data);
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
			print_error("No exit(E) found on the map",data);
		else
			print_error("Map contains multiple exits",data);
	}
	if (data->map.count_p != 1)
	{
		if (data->map.count_p == 0)
			print_error( "No player(P) found on the map",data);
		else
			print_error("Map contains multiple players",data);
	}
}

void	check_map_size(t_data *data);


void	check_map(t_data *data)
{
	if (data->ac > 2)
		print_error("2 or more maps in arguments",data);
	check_map_name(data);
	read_map(data);
	is_it_rectanguler(data);
	to_the_grid(data);
	is_it_surrounded(data);
	check_features(data);
}

int main(int ac,char **av)
{
	t_data	data;

	start_data(&data, av, ac);
	check_map(&data);
	int i  = 0;
	while (i < data.map.y_max)
	{
		printf("i: %d || %s",i, data.map.grid[i]);
		i++;
	}
	all_free(data.map.grid);
}
