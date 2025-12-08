#include "so_long.h"

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
	{
		data->game.w_flag = 1;
		data->p_y--;
	}
	else if (keycode == S)
	{
		data->game.s_flag = 1;
		data->p_y++;
	}
	else if (keycode == A)
	{
		data->game.a_flag = 1;
		data->p_x--;
	}
	else if (keycode == D)
	{
		data->game.d_flag = 1;
		data->p_x++;
	}
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
	{
		player_move(data, keycode);
		update_map(data, old_x, old_y);
	}
	render(data);
	return (0);
}
