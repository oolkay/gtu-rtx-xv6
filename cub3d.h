#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAP_HEIGHT 10
#define MAP_WIDTH 10


typedef struct s_player
{
    double x;
    double y;
    double speed;
    double direction;
    double angle;
    double dx;
    double dy;
} t_player;

typedef struct s_img
{
	int		height;
	int		width;
	void	*i;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}   t_img;

typedef struct s_texture
{
    t_img *north;
    t_img *south;
    t_img *west;
    t_img *east;
} t_texture;


typedef struct s_game
{
    void *mlx;
    void *win;
    t_player pl;
    t_img img;
    void* floor;
    void* wall;
    int **map;
} t_game;

typedef struct s_fVector
{
    double x;
    double y;
} t_dVector;

typedef struct s_iVector
{
    int x;
    int y;
} t_iVector;



void rayCasting(const t_game *game, t_dVector *endPoint, double angle);

#endif