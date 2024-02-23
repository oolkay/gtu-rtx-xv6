#ifndef CUB3D_H
# define CUB3D_H

#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAP_HEIGHT 10
#define MAP_WIDTH 10


typedef struct s_player
{
    float x;
    float y;
    float speed;
    float direction;
    float angle;
    float dx;
    float dy;
    float angledrad;
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
    t_img texture;
    void* floor;
    void* wall;
    void* bg;
    int **map;
} t_game;

typedef struct s_fVector
{
    float x;
    float y;
} t_dVector;

typedef struct s_iVector
{
    int x;
    int y;
} t_iVector;



void rayCasting(const t_game *game, t_dVector *endPoint, float *dist, float angle);
void rayCasting2(const t_game *game, t_dVector *endPoint, float *dist, float *wall_x, float angle);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_img *data, int x, int y);
void	my_mlx_area_put(t_img *d, t_dVector p, t_dVector dim, int c);
void	mlx_img_to_img(int p[2], t_img img[2], int c1);


#endif