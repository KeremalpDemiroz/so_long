#include "so_long.h"

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

	height = 128;
	width = 128;
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, P_F, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.p_f, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, P_B, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.p_b, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, P_R, &width, &height);
	img_ptr = swap_img_ptr(img_ptr, &data->img.p_r, data);
	img_ptr = mlx_xpm_file_to_image(data->game.mlx, P_L, &width, &height);
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

void	choose_direction(t_data *data, int x, int y)
{
	if (!data->game.w_flag && !data->game.s_flag
		&& !data->game.a_flag && !data->game.d_flag)
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.p_f, x * 128, y * 128);
	if (data->game.w_flag)
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.p_b, x * 128, y * 128);
	else if (data->game.s_flag)
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.p_f, x * 128, y * 128);
	else if (data->game.a_flag)
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.p_l, x * 128, y * 128);
	else if (data->game.d_flag)
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.p_r, x * 128, y * 128);
	data->game.w_flag = 0;
	data->game.s_flag = 0;
	data->game.a_flag = 0;
	data->game.d_flag = 0;
}

void	print_image_to_window(t_data *data, int x, int y)
{
	if (data->map.grid[y][x] == '1')
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.wall, x * 128, y * 128);
	if (data->map.grid[y][x] == '0')
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.floor, x * 128, y * 128);
	if (data->map.grid[y][x] == 'E')
	{
		if (data->map.count_c > 0)
			mlx_put_image_to_window(data->game.mlx,
				data->game.win, data->img.e_c, x * 128, y * 128);
		else
			mlx_put_image_to_window(data->game.mlx,
				data->game.win, data->img.e_o, x * 128, y * 128);
	}
	if (data->map.grid[y][x] == 'P')
		choose_direction(data, x, y);
	if (data->map.grid[y][x] == 'C')
		mlx_put_image_to_window(data->game.mlx,
			data->game.win, data->img.coin, x * 128, y * 128);
}

int	render(t_data *data)
{
	int	x;
	int	y;

	y = 0;
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
	return (0);
}
