#include "cub3d.h"
#include <unistd.h>
#include <math.h>

# define A 97
# define S 115
# define D 100
# define W 119
# define ESC 65307
# define LEFT 65361
# define RIGHT 65363
# define Q 113
# define E 101
# define M 109
# define PI 3.14159265359
# define deltaSabit 5
# define TILE_SIZE 40
# define MAP_WIDTH 600
# define MAP_HEIGHT 600
# define FPS 120


static t_game init_game()
{
    t_game game;
    game.mlx = NULL;
    game.mlx = mlx_init();
    game.pl.x = 128;
    game.pl.y = 128;
    game.pl.angle = 0;
    game.pl.dx = deltaSabit * cos(game.pl.angle);
    game.pl.dy = deltaSabit * sin(game.pl.angle);

    game.keys.w = 0;
    game.keys.a = 0;
    game.keys.s = 0;
    game.keys.d = 0;
    game.keys.esc = 0;
    game.keys.q = 0;
    game.keys.left = 0;
    game.keys.right = 0;
    game.keys.e = 0;
    game.keys.m = 0;

    game.frame = 0;
    return game;
}

static void drawLine(t_game *game)
{
    int x = game->pl.x + 20;
    int y = game->pl.y + 20;
    int x1 = x + 64 * cos(game->pl.angle);
    int y1 = y + 64 * sin(game->pl.angle);
    int dx = abs(x1 - x);
    int dy = abs(y1 - y);
    int sx = x < x1 ? 1 : -1;
    int sy = y < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;
    while (1)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, 0x00ff00);
        if (x == x1 && y == y1)
            break;
        e2 = err;
        if (e2 > -dx)
        {
            err -= dy;
            x += sx;
        }
        if (e2 < dy)
        {
            err += dx;
            y += sy;
        }
    }
}

static void cub_update(void *param)
{
    t_game *g;

    g = param;
}

static int drawPlayer(void *_game)
{
    t_game *game = _game;
    for (int i = 0; i < TILE_SIZE; ++i)
    {
        for (int  j = 0; j < TILE_SIZE; j++)
        {
            mlx_pixel_put(game->mlx, game->win, game->pl.x + i, game->pl.y + j, 0xff0000);
        }
    }
    drawLine(game);
    return (1);
}

static int drawMap(t_game *game)
{
    for (int i = 0; i < MAP_HEIGHT / TILE_SIZE; ++i)
    {
        for (int j = 0; j < MAP_WIDTH / TILE_SIZE; j++)
        {
            mlx_put_image_to_window(game->mlx, game->win, game->image, i * TILE_SIZE, j * TILE_SIZE);
        }
    }
    return (1);
}

static int movePlayer(void *_game)
{
    t_game *game = _game;
    if (game->keys.w)
    {
        game->pl.x += game->pl.dx;
        game->pl.y += game->pl.dy;
    }
	if (game->keys.s)
    {
        game->pl.x -= game->pl.dx;
        game->pl.y -= game->pl.dy;
    }
    if (game->keys.a)
    {
        game->pl.x -= deltaSabit * cos(game->pl.angle + PI / 2);
        game->pl.y -= deltaSabit * sin(game->pl.angle + PI / 2);
    }
    if (game->keys.d)
    {
        game->pl.x += deltaSabit * cos(game->pl.angle + PI / 2);
        game->pl.y += deltaSabit * sin(game->pl.angle + PI / 2);
    }
	if (game->keys.left)
    {
        game->pl.angle -= 0.1;
        if (game->pl.angle < 0)
            game->pl.angle += 2 * PI;
        game->pl.dx = deltaSabit * cos(game->pl.angle);
        game->pl.dy = deltaSabit * sin(game->pl.angle);
    }
	if (game->keys.right)
    {
        game->pl.angle += 0.1;
        if (game->pl.angle > 2 * PI)
            game->pl.angle -= 2 * PI;
        game->pl.dx = deltaSabit * cos(game->pl.angle);
        game->pl.dy = deltaSabit * sin(game->pl.angle);
    }
}

int keydown(int keycode, void *param)
{
    t_game *game = param;
    if (keycode == W)
        game->keys.w = 1;
    if (keycode == A)
        game->keys.a = 1;
    if (keycode == S)
        game->keys.s = 1;
    if (keycode == D)
        game->keys.d = 1;
    if (keycode == LEFT)
        game->keys.left = 1;
    if (keycode == RIGHT)
        game->keys.right = 1;
    if (keycode == E)
        game->keys.e = 1;
    if (keycode == M)
        game->keys.m = 1;
    if (keycode == ESC || keycode == Q)
        exit(0);

    return (1);
}

int keyup(int keycode, void *param)
{
    t_game *game = param;

    if (keycode == W)
        game->keys.w = 0;
    if (keycode == A)
        game->keys.a = 0;
    if (keycode == S)
        game->keys.s = 0;
    if (keycode == D)
        game->keys.d = 0;
    if (keycode == LEFT)
        game->keys.left = 0;
    if (keycode == RIGHT)
        game->keys.right = 0;
    return (1);
}

void myGame(t_game *g)
{
    if(g->frame++ % FPS == 0){
        movePlayer(g);
        drawMap(g);
        drawPlayer(g);
    }
}

int main()
{
    t_game game = init_game();
    int x , y;
    // game.image = mlx_xpm_file_to_image(game.mlx, "textures/wall_1.xpm", &x, &y);
    game.win = mlx_new_window(game.mlx, MAP_WIDTH, MAP_HEIGHT, "CUB3D");

    void *img = mlx_xpm_file_to_image(game.mlx, "textures/bg2.xpm", &x, &y);
    game.image = img;
    mlx_hook(game.win, 2, 1L<<0, &keydown, &game);
    mlx_hook(game.win, 3, 1L<<1, &keyup, &game);
	mlx_loop_hook(game.mlx, &myGame, &game);
    mlx_loop(game.mlx);
}