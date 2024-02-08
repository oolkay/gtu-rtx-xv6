#include "cub3d.h"
#include <unistd.h>
#include <math.h>

# define A 97
# define S 115
# define D 100
# define W 119
# define ESC 53
# define PI 3.14159265359
# define deltaSabit 5


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
    return game;
}

static void drawLine(t_game *game)
{
    int x = game->pl.x;
    int y = game->pl.y;
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
    for (int i = 0; i < 16; ++i)
    {
        for (int  j = 0; j < 16; j++)
        {
            mlx_pixel_put(game->mlx, game->win, game->pl.x + i, game->pl.y + j, 0xff0000);
        }
    }
    for (int i = 0; i < 16; ++i)
    {
        for (int  j = 0; j < 16; j++)
        {
            mlx_pixel_put(game->mlx, game->win, game->pl.x + i, game->pl.y + j, 0xff0000);
        }
    }
    drawLine(game);
    return (1);
}

static int drawMap(t_game *game)
{
    for (int i = 0; i < 320 / 64; ++i)
    {
        for (int j = 0; j < 320 / 64; j++)
        {
            mlx_put_image_to_window(game->mlx, game->win, game->image, i * 64, j * 64);
        }
    }
    return (1);
}

static int movePlayer(int keycode, void *_game)
{
    t_game *game = _game;
    if (keycode == W)
    {
        game->pl.x += game->pl.dx;
        game->pl.y += game->pl.dy;
    }
	if (keycode == S)
    {
        game->pl.x -= game->pl.dx;
        game->pl.y -= game->pl.dy;
    }
	if (keycode == A)
    {
        game->pl.angle -= 0.1;
        if (game->pl.angle < 0)
            game->pl.angle += 2 * PI;
        game->pl.dx = deltaSabit * cos(game->pl.angle);
        game->pl.dy = deltaSabit * sin(game->pl.angle);
    }
	if (keycode == D)
    {
        game->pl.angle += 0.1;
        if (game->pl.angle > 2 * PI)
            game->pl.angle -= 2 * PI;
        game->pl.dx = deltaSabit * cos(game->pl.angle);
        game->pl.dy = deltaSabit * sin(game->pl.angle);
    }
    drawMap(game);
    drawPlayer(game);

}

int main()
{
    t_game game = init_game();
    int x , y;
    // game.image = mlx_xpm_file_to_image(game.mlx, "textures/wall_1.xpm", &x, &y);
    game.win = mlx_new_window(game.mlx, 320, 320, "CUB3D");

    void *img = mlx_xpm_file_to_image(game.mlx, "textures/bg2.xpm", &x, &y);
    game.image = img;
    drawMap(&game);
    mlx_hook(game.win, 02, 1L << 0, &movePlayer, &game);
    mlx_loop(game.mlx);

}