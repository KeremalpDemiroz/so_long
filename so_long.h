#ifndef SO_LONG_H
# define SO_LONG_H

# include "minilibx-linux/mlx.h"
# include "sources/libft.h"
# include <stdio.h>
# include <fcntl.h>

# define P_F "./textures/walle_front.xpm"
# define P_B "./textures/walle_back.xpm"
# define FLOOR "./textures/test_tile_floor.xpm"
# define WALL "./textures/test_tile_wall.xpm"
# define COIN "./textures/test_tile_coin.xpm"
# define E_O "./textures/little_knight_right.xpm"
# define E_C "./textures/little_knight_left.xpm"

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
}t_game;

typedef struct s_list
{
	char	*line;
	int		len;

	struct s_list	*next;
}t_list;


typedef struct s_map
{
	char	**grid;
	int		y_max;
	int		x_max;
	int		count_c;
	int		count_p;
	int		count_e;
}t_map;


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

}t_image;


typedef struct s_data
{
	t_game	game;
	t_map	map;
	t_image	img;
	t_list	*list;
	char	**av;
	int		map_fd;
	int		ac;
	int		p_x;
	int		p_y;
	int		e_x;
	int		e_y;
	int		moves_count;

}t_data;


#endif