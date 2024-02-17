SRC = main.c

LMLX = -lmlx -lXext -lX11 -lm

all:
	gcc main.c ray_casting.c ${LMLX} -o cub3d
	./cub3d
