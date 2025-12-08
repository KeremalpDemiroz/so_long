NAME= so_long
CC= cc
CFLAGS= -Wall -Werror -Wextra -g
MLX_FLAGS= -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz

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
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(SRCS) $(LIBFT_A) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)

fclean:clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re

#cc -g -std=gnu89 so_long.c sources/libft.a -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -o so_long

#valgrind --track-origins=yes --show-leak-kinds=all -s --leak-check=full --track-fds=yes