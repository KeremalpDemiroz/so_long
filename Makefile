NAME= so_long
CC= cc
CFLAGS= -Wall -Werror -Wextra -g
MLX_FLAGS= -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz
MLX_GIT = git@github.com:42paris/minilibx-linux.git

SRCS=	so_long.c\
		clean_data.c\
		clean_exit.c\
		init_data.c\
		map_checker.c\
		map_utils.c\
		node_utils.c\
		player_movement.c\
		utils.c\
		render.c

MLX= ./minilibx-linux
LIBFT= ./includes
LIBFT_A= $(LIBFT)/libft.a

OBJS= $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all:$(NAME)
$(NAME):$(OBJS)
	@make -C $(MLX)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT_A) $(MLX_FLAGS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)


fclean:clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)
	@make clean -C $(MLX)

clone:
	git clone $(MLX_GIT)

remove_clone:$(MLX)
	rm -rf $(MLX)

re: fclean all

.PHONY: all clean fclean re clone remove_clone

