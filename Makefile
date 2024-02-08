SRC = main.c

LMLX = -lmlx -lXext -lX11 -lm

all:
	gcc main.c ${LMLX} -o cub3d
	./cub3d
