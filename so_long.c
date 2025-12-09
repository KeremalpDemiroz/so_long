/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:16:40 by kedemiro          #+#    #+#             */
/*   Updated: 2025/12/09 03:20:34 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	start_data(t_data *data, char **av, int ac)
{
	data->map_name = NULL;
	data->av = av;
	data->ac = ac;
	data->list = NULL;
	data->map_fd = -1;
	data->moves_count = 0;
	start_game_data(&(data->game));
	start_map_data(&(data->map));
	start_image_data(&(data->img));
}

void	check_map(t_data *data)
{
	if (data->ac != 2)
		print_error("Format must be like ./so_long <map.ber>", data);
	check_map_name(data);
	read_map(data);
	is_it_rectanguler(data);
	to_the_grid(data);
	is_it_surrounded(data);
	check_features(data);
	get_position(data);
	is_it_playable(data);
	data->game.height = (data->map.y_max) * 128;
	data->game.width = (data->map.x_max) * 128;
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
	mlx_hook(data.game.win, 2, 1, key_handler, &data);
	mlx_hook(data.game.win, 17, 0, close_window, &data);
	mlx_expose_hook(data.game.win, render, &data);
	render(&data);
	mlx_loop(data.game.mlx);
	return (0);
}
