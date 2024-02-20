#include "cub3d.h"
#include <unistd.h>
#include <math.h>

#define A 97
#define S 115
#define D 100
#define W 119
#define ESC 53
#define PI 3.14159265359
#define lineLen 16
#define winWidth 1280
#define winHeight 640
#define FOV 30
#define FOVrad (FOV * PI / 180)

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
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

static t_game init_game()
{
    t_game game;
    game.mlx = NULL;
    game.mlx = mlx_init();
    game.pl.x = 120;
    game.pl.y = 120;
    game.pl.angle = PI/4;
    game.pl.dx = lineLen * cos(game.pl.angle);
    game.pl.dy = lineLen * sin(game.pl.angle);
    game.pl.angledrad = (2 * (float)FOVrad / (float)(winWidth/2));
    game.map = (int **)malloc(sizeof(int *) * MAP_HEIGHT);
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        game.map[i] = (int *)malloc(sizeof(int) * MAP_WIDTH);
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            game.map[i][j] = map[i][j];
        }
    }
    return game;
}

// static void drawDebug(double bx, double by, double ex, double ey, t_game *game, int color)
// {
//     double x = bx;
//     double y = by;
//     if (bx == ex && by == ey)
//         return;
//     double step = fabs(ex - bx);
//     if (fabs(ey - by) > step)
//         step = fabs(ey - by);
//     double xInc = (ex - bx) / step;
//     double yInc = (ey - by) / step;
//     for (int i = 0; i < step; i++)
//     {
//         mlx_pixel_put(game->mlx, game->win, x, y, color);
//         x += xInc;
//         y += yInc;
//     }
// }


static void draw3Dline(t_game *game, int x1, int y2, int color)
{
    x1 = (winWidth / 2) + x1;

    for (int i = 0; i < y2 / 2; i++)
    {
        mlx_pixel_put(game->mlx, game->win, x1, winHeight / 2 + i, color);
        mlx_pixel_put(game->mlx, game->win, x1, winHeight / 2 - i, color);
    }
}

static void drawLine(t_game *game, double angle)
{
    double beginx = game->pl.x + 16 / 2;
    double beginy = game->pl.y + 16 / 2;
    t_dVector endPoint;
    double endx = beginx;
    double endy = beginy;
    double dist = 0;

    double ang = angle;

    double dx, dy, x1, y1, x2, y2;
    double x0, y0;
    double distV, distH;

    rayCasting(game, &endPoint, &dist, angle);

    endx = endPoint.x;
    endy = endPoint.y;
    double x = beginx;
    double y = beginy;
    double step = fabs(endx - beginx);
    if (fabs(endy - beginy) > step)
        step = fabs(endy - beginy);
    double xInc = (endx - beginx) / step;
    double yInc = (endy - beginy) / step;
    for (int i = 0; i < step; i++)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, 0xff00ff);
        x += xInc;
        y += yInc;
    }

	double wall_height = (int)((winHeight * 50) / (dist));
    draw3Dline(game, (fabs((game->pl.angle - ang) - FOVrad)) * (winWidth/2), wall_height, 0xff00ff - powf(1.14, dist / 7));
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
        for (int j = 0; j < 16; j++)
        {
            mlx_pixel_put(game->mlx, game->win, game->pl.x + i, game->pl.y + j, 0xff0000);
        }
    }
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; j++)
        {
            mlx_pixel_put(game->mlx, game->win, game->pl.x + i, game->pl.y + j, 0xff0000);
        }
    }
    drawLine(game, game->pl.angle);
    for (int i = 1; i < (winWidth/4); i++)
    {
        drawLine(game, game->pl.angle + (float)(i * game->pl.angledrad));
        drawLine(game, game->pl.angle - (float)(i * game->pl.angledrad));
    }
    return (1);
}

static int drawMap(t_game *game)
{
    mlx_put_image_to_window(game->mlx, game->win, game->bg, winWidth/2, 0);
    for (int i = 0; i < MAP_HEIGHT; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
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
    for (int i = winWidth/2; i < winWidth; i++)
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
    int x, y;
    x = 640;
    y = 640;
    // game.image = mlx_xpm_file_to_image(game.mlx, "textures/wall_1.xpm", &x, &y);
    game.win = mlx_new_window(game.mlx, winWidth, winHeight, "CUB3D");

    void *img = mlx_xpm_file_to_image(game.mlx, "textures/bg2.xpm",  &x, &y);
    game.floor = img;
    game.wall = mlx_xpm_file_to_image(game.mlx, "textures/wall.xpm", &x, &y);
    game.bg = mlx_xpm_file_to_image(game.mlx, "textures/fc.xpm", &x, &y);
    drawMap(&game);
    mlx_hook(game.win, 02, 1L << 0, &movePlayer, &game);
    mlx_loop(game.mlx);
}