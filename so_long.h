#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_game
{
	void	*mlx;
	void	*win;

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
	void	*exit;
	void	*coin;
	void	*player;

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
	int		moves_count;

}t_data;


#endif