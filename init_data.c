#include "so_long.h"

void	start_game_data(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->height = 0;
	game->width = 0;
	game->w_flag = 0;
	game->s_flag = 0;
	game->a_flag = 0;
	game->d_flag = 0;
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
