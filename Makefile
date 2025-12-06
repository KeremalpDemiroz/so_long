cc -g -std=gnu89 so_long.c sources/libft.a -Lminilibx-linux -lmlx_Linux -L/usr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -o so_long

valgrind --track-origins=yes --show-leak-kinds=all -s --leak-check=full --track-fds=yes