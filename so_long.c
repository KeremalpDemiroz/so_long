#include "minilibx-linux/mlx.h"
#include "so_long.h"
#include "sources/libft.h"
#include <stdio.h>
#include <fcntl.h>

void	start_game_data(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
}

void	start_map_data(t_map *map)
{
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
	start_game_data(&(data->game));
	start_map_data(&(data->map));
	start_image_data(&(data->img));
}

void	check_map_name(char **av)
{
	int	i;
	int	j;
	char	*ext;

	i = 0;
	ext = ".ber";
	if (!av[1] || ft_strlen(av[1]) < 4)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("File name doesn't exist", 2);
		exit(EXIT_FAILURE);
	}
	while (av[1][i])
	{
		j = 0;
		while (av[1][i + j] && ext[j] == av[1][i + j])
		j++;
		if (ext[j] == '\0' && !av[1][i + j])
		return ;
		i++;
	}
	ft_putendl_fd("Error", 2);
	ft_putendl_fd("File extension is not valid", 2);
	exit(EXIT_FAILURE);
}

void	count_features(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'P')
			map->count_p++;
		else if (line[i] == 'C')
			map->count_c++;
		else if (line[i] == 'E')
			map->count_e++;
		i++;
	}
}

void	print_error(char *err_msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err_msg, 2);
	exit(EXIT_FAILURE);
}
void	free_node(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
	*list = NULL;
}
t_list	*new_node(char *line, int len, t_data *data)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
	{
		free_node(&data->list);
		print_error("Map file can not be read");
	}
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


// void	to_the_grid()
// {
// 	while (list)


// }

void	is_it_rectanguler(t_data *data)
{
	t_list	*tmp;
	int		y;
	int		x;

	tmp = data->list;
	x = tmp->len;
	while (tmp)
	{
		if (tmp->len != x)
		{
			free_node(&data->list);
			print_error("Map is not rectanguler");
		}
		tmp = tmp->next;
	}
}

void	read_map(t_data *data, int map_fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
			break ;
		add_back(&data->list, new_node(line, ft_strlen(line), data));
		count_features(line, &(data->map));
	}
	close(map_fd);
	if (!data->list)
		print_error("Map file can not be read");
}

void	is_it_surrounded(t_data *data)
{

}

void	check_map(t_data *data)
{
	int	map_fd;
	char *read;

	check_map_name(data->av);
	map_fd = open(data->av[1], O_RDONLY);
	if (map_fd < 0)
		print_error("Map file can not be read");
	read_map(data, map_fd);
	is_it_rectanguler(data);
}

int main(int ac,char **av)
{
	t_data	data;
	start_data(&data, av, ac);
	check_map(&data);
	// int i  =0;
	// while (i < 5)
	// {
	// 	printf("%s", data.map.grid[i]);
	// 	i++;
	// }
}
