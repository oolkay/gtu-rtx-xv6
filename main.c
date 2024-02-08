#include "cub3d.h"
#include <unistd.h>
#include <math.h>

# define A 97
# define S 115
# define D 100
# define W 119
# define ESC 53
# define PI 3.14159265359
# define lineLen 16
# define mapWidth 10
# define mapHeight 10
# define winWidth 640
# define winHeight 640


int map[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


static t_game init_game()
{
    t_game game;
    game.mlx = NULL;
    game.mlx = mlx_init();
    game.pl.x = 128;
    game.pl.y = 128;
    game.pl.angle = 0;
    game.pl.dx = lineLen * cos(game.pl.angle);
    game.pl.dy = lineLen * sin(game.pl.angle);
    return game;
}

static void drawLine(t_game *game)
{
    float beginx = game->pl.x + 8;
    float beginy = game->pl.y + 8;

    float endx = 0;
    float endy = 0;
        endx = beginx;
        endy = beginy;
    while (map[(int)endy / 64][(int)endx / 64] != 1)
    {
        if (endx < 0 || endx > mapWidth * 64 || endy < 0 || endy > mapHeight * 64)
            break;
        if (map[(int)endy / 64][(int)endx / 64] == 1)
            break;
        endx += cos(game->pl.angle);
        endy += sin(game->pl.angle);
    }
    endx -= cos(game->pl.angle);

    // float endx = beginx + 64 * cos(game->pl.angle);
    // float endy = beginy + 64 * sin(game->pl.angle);
    float x = beginx;
    float y = beginy;
    float step = fabs(endx-beginx);
    if (fabs(endy - beginy) > step)
        step = fabs(endy - beginy);
    float xInc = (endx - beginx) / step;
    float yInc = (endy - beginy) / step;
    for (int i = 0; i < step; i++)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, 0xff0000);
        x += xInc;
        y += yInc;
    }
    
    // float dx = 64 * cos(game->pl.angle);
    // float dy = 64 * sin(game->pl.angle);
    // float px = game->pl.x+8;
    // float py = game->pl.y+8;
    // if (game->pl.angle > 0 && game->pl.angle < PI / 2)
    //     for (float i = px+dx, j = py + dy; i > px && j > py; i -= 1*cos(game->pl.angle), j -= 1*sin(game->pl.angle))
    //         mlx_pixel_put(game->mlx, game->win, i, j, 0xff0000);
    // else if (game->pl.angle > PI / 2 && game->pl.angle < PI)
    //     for (float i = px+dx, j = py + dy; i < px && j > py; i -= 1*cos(game->pl.angle), j -= 1*sin(game->pl.angle))
    //         mlx_pixel_put(game->mlx, game->win, i, j, 0xff0000);
    // else if (game->pl.angle > PI && game->pl.angle < 3 * PI / 2)
    //     for (float i = px+dx, j = py + dy; i < px && j < py; i -= 1*cos(game->pl.angle), j -= 1*sin(game->pl.angle))
    //         mlx_pixel_put(game->mlx, game->win, i, j, 0xff0000);
    // else if (game->pl.angle > 3 * PI / 2 && game->pl.angle < 2 * PI)
    //     for (float i = px+dx, j = py + dy; i > px && j < py; i -= 1*cos(game->pl.angle), j -= 1*sin(game->pl.angle))
    //         mlx_pixel_put(game->mlx, game->win, i, j, 0xff0000);
}

static void cub_update(void *param)
{
    t_game *g;

    g = param;
}

// static int rayCasting(void *_game)
// {
//     t_game *game = _game;
//     drawMap(game);
//     drawPlayer(game);
//     return (1);
// }

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
    for (int i = 0; i < mapHeight; ++i)
    {
        for (int j = 0; j < mapWidth; j++)
        {
            if (map[i][j] == 1)
            {
                mlx_put_image_to_window(game->mlx, game->win, game->wall, j * 64, i * 64);
            }
            else
            {
                mlx_put_image_to_window(game->mlx, game->win, game->floor, j * 64, i * 64);
            }
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
        game->pl.dx = lineLen * cos(game->pl.angle);
        game->pl.dy = lineLen * sin(game->pl.angle);
    }
	if (keycode == D)
    {
        game->pl.angle += 0.1;
        if (game->pl.angle > 2 * PI)
            game->pl.angle -= 2 * PI;
        game->pl.dx = lineLen * cos(game->pl.angle);
        game->pl.dy = lineLen * sin(game->pl.angle);
    }
    drawMap(game);
    drawPlayer(game);

}

int main()
{
    t_game game = init_game();
    int x , y;
    // game.image = mlx_xpm_file_to_image(game.mlx, "textures/wall_1.xpm", &x, &y);
    game.win = mlx_new_window(game.mlx, winWidth, winHeight, "CUB3D");

    void *img = mlx_xpm_file_to_image(game.mlx, "textures/bg2.xpm", &x, &y);
    game.floor = img;
    game.wall = mlx_xpm_file_to_image(game.mlx, "textures/wall.xpm", &x, &y);
    drawMap(&game);
    mlx_hook(game.win, 02, 1L << 0, &movePlayer, &game);
    mlx_loop(game.mlx);

}