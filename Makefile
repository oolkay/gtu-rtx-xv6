SRC = main.c

LMLX = -lmlx -lXext -lX11 -lm

ifeq ($(UNAME), Macos)
	LMLX = mlx/libmlx.a -framework OpenGL -framework AppKit -lm
endif

all:
	gcc main.c ray_casting.c my_mlx.c ${LMLX} -o cub3d
	./cub3d
