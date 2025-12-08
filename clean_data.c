#include "so_long.h"

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
