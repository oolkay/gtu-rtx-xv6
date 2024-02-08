#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct s_player
{
    float x;
    float y;
    float speed;
    float direction;
    float angle;
    float dx;
    float dy;
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
    void* image;
} t_game;

#endif