SRC = main.c

LMLX = -framework OpenGL -framework AppKit -lm

all:
	gcc main.c ray_casting.c my_mlx.c mlx/libmlx.a ${LMLX} -o cub3d
	./cub3d
