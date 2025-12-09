/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kedemiro <kedemiro@student.42istanbul.com. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 17:17:19 by kedemiro          #+#    #+#             */
/*   Updated: 2025/12/08 23:05:54 by kedemiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "includes/libft.h"
# include <stdio.h>
# include <fcntl.h>

# define P_F "./textures/player_front.xpm"
# define P_B "./textures/player_back.xpm"
# define P_L "./textures/player_left.xpm"
# define P_R "./textures/player_right.xpm"
# define FLOOR "./textures/floor.xpm"
# define WALL "./textures/wall.xpm"
# define COIN "./textures/coin.xpm"
# define E_O "./textures/exit_o.xpm"
# define E_C "./textures/exit_c.xpm"

# define ESC 65307

# define W 119

# define A 97

# define S 115

# define D 100

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
	int		w_flag;
	int		s_flag;
	int		a_flag;
	int		d_flag;
}	t_game;

typedef struct s_list
{
	char			*line;
	int				len;
	struct s_list	*next;
}	t_list;

typedef struct s_map
{
	char	**grid;
	int		y_max;
	int		x_max;
	int		count_c;
	int		count_p;
	int		count_e;
}	t_map;

typedef struct s_image
{
	void	*floor;
	void	*wall;
	void	*coin;
	void	*e_o;
	void	*e_c;
	void	*p_f;
	void	*p_b;
	void	*p_r;
	void	*p_l;
}	t_image;

typedef struct s_data
{
	t_game	game;
	t_map	map;
	t_image	img;
	t_list	*list;
	char	**av;
	char	*map_name;
	int		map_fd;
	int		ac;
	int		p_x;
	int		p_y;
	int		e_x;
	int		e_y;
	int		moves_count;
}	t_data;

void	start_data(t_data *data, char **av, int ac);
void	start_game_data(t_game *game);
void	start_map_data(t_map *map);
void	start_image_data(t_image *img);
void	check_screen_size(t_data *data);
void	get_img_ptr(t_data *data);
void	*swap_img_ptr(void	*img_ptr, void	**img_id, t_data *data);
void	choose_direction(t_data *data, int x, int y);
void	print_image_to_window(t_data *data, int x, int y);
int		render(t_data *data);
void	flood_fill(char	**map_copy, int x, int y, t_data *data);
void	check_map(t_data *data);
void	clean_game_data(t_game *game);
void	clean_map_data(t_map *map);
void	clean_image_data(t_image *img);
void	clean_data(t_data *data);
void	reinitialize_image(t_data *data);
void	destroy_images(t_data *data);
void	clean_exit(t_data *data, char *err_msg);
int		close_window(void	*param);
void	read_map(t_data *data);
void	check_map_name(t_data *data);
void	is_it_rectanguler(t_data *data);
void	is_it_surrounded(t_data *data);
void	is_it_playable(t_data *data);
void	get_position(t_data *data);
void	to_the_grid(t_data *data);
void	check_features(t_data *data);
char	**create_map_copy(t_data *data);
void	count_features(char *line, t_data *data, int *flag);
void	free_node(t_list **list);
void	add_back(t_list **list, t_list *new);
int		count_node(t_data *data);
t_list	*new_node(char *line, t_data *data);
void	update_map(t_data *data, int old_x, int old_y);
void	player_move(t_data *data, int keycode);
int		key_handler(int keycode, void *param);
void	all_free(char **split);
void	print_error(char *err_msg, t_data *data);

#endif
