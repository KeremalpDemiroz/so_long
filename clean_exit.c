/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:16:50 by kedemiro          #+#    #+#             */
/*   Updated: 2025/12/08 17:16:51 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

int	close_window(void	*param)
{
	clean_exit(param, NULL);
	return (0);
}
