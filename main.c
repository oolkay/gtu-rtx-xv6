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
#define mapWidth 10
#define mapHeight 10
#define winWidth 640
#define winHeight 640
#define FOV 60

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
    game.pl.x = 128;
    game.pl.y = 128;
    game.pl.angle = 0;
    game.pl.dx = lineLen * cos(game.pl.angle);
    game.pl.dy = lineLen * sin(game.pl.angle);
    return game;
}

// static void drawDebug(float bx, float by, float ex, float ey, t_game *game, int color)
// {
//     float x = bx;
//     float y = by;
//     if (bx == ex && by == ey)
//         return;
//     float step = fabs(ex - bx);
//     if (fabs(ey - by) > step)
//         step = fabs(ey - by);
//     float xInc = (ex - bx) / step;
//     float yInc = (ey - by) / step;
//     for (int i = 0; i < step; i++)
//     {
//         mlx_pixel_put(game->mlx, game->win, x, y, color);
//         x += xInc;
//         y += yInc;
//     }
// }

static void drawLine(t_game *game, float angle)
{
    float beginx = game->pl.x + 16 / 2;
    float beginy = game->pl.y + 16 / 2;
    float endx = beginx;
    float endy = beginy;

    float ang = angle;
    if((tan(ang) < 0.001 && tan(ang) > -0.001) || (tan(ang) > 999 || tan(ang) < -999))
        return;

    float dx, dy, x1, y1, x2, y2;
    float x0, y0;
    float distV, distH;

    if (ang > PI / 2 && ang < 3 * PI / 2) // looking left
    {
        x1 = ((int)beginx / 64) * 64 - 0.0001; // -0.0001 to detect the wall from map index or it will never detect the wall
        y1 = beginy - (beginx - x1) * tan(ang); 
        x0 = -64; // goind left so x0 is -64
        y0 = -64 * tan(ang);
    }
    else if (ang < PI / 2 || ang > 3 * PI / 2) // looking right
    {
        x1 = ((int)beginx / 64) * 64 + 64; // ((int)beginx / 64) * 64 gives us the closest left wall so we add 64 to get the closest right wall
        y1 = beginy - (beginx - x1) * tan(ang);
        x0 = 64; // goind right so x0 is 64
        y0 = 64 * tan(ang);
    }
    for (int i = 0; i < 10; i++) // 10 TILE is the max distance our ray can travel
    {
        if((int)y1 / 64 < 0 || (int)y1 / 64 > mapHeight || (int)x1 / 64 < 0 || (int)x1 / 64 > mapWidth) // if we are out of the map
            break;
        if (map[(int)y1 / 64][(int)x1 / 64] == 1) // if we hit a wall
            break;
        x1 += x0;
        y1 += y0; 
    }
    // drawDebug(beginx, beginy, x1, y1, game, 0x0000ff);

    distV = sqrt(pow(x1 - game->pl.x, 2) + pow(y1 - game->pl.y, 2)); // distance from the player to the Vertical wall

    if (ang > 0 && ang < PI) // looking down
    {
        y2 = ((int)beginy / 64) * 64 + 64; // ((int)beginy / 64) * 64 gives us the closest up wall so we add 64 to get the closest down wall
        x2 = beginx - (beginy - y2) / tan(ang); 
        y0 = 64; // goind down so y0 is 64
        x0 = 64 / tan(ang);
    }
    else if (ang > PI && ang < 2 * PI) // looking up
    {
        y2 = ((int)beginy / 64) * 64 - 0.0001; // -0.0001 to detect the wall from map index or it will never detect the wall
        x2 = beginx - (beginy - y2) / tan(ang);
        y0 = -64; // goind up so y0 is -64
        x0 = -64 / tan(ang);
    }
    for (int i = 0; i < 10; i++) // 10 TILE is the max distance our ray can travel
    {
        if((int)y2 / 64 < 0 || (int)y2 / 64 > mapHeight || (int)x2 / 64 < 0 || (int)x2 / 64 > mapWidth)
            break;
        if (map[(int)y2 / 64][(int)x2 / 64] == 1)
            break;
        x2 += x0;
        y2 += y0;
    }
    // drawDebug(beginx, beginy, x2, y2, game, 0xff00ff);

    distH = sqrt(pow(x2 - game->pl.x, 2) + pow(y2 - game->pl.y, 2));    // distance from the player to the Horizontal wall

    if(distV < distH)
    {
        endx = x1;
        endy = y1;
    }
    else
    {
        endx = x2;
        endy = y2;
    }

    float x = beginx;
    float y = beginy;
    float step = fabs(endx - beginx);
    if (fabs(endy - beginy) > step)
        step = fabs(endy - beginy);
    float xInc = (endx - beginx) / step;
    float yInc = (endy - beginy) / step;
    for (int i = 0; i < step; i++)
    {
        mlx_pixel_put(game->mlx, game->win, x, y, 0xff00ff);
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
    for (int i = 0; i < FOV; i++)
    {
        drawLine(game, game->pl.angle - PI / 6 + i * PI / 180);
    }
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
    int x, y;
    // game.image = mlx_xpm_file_to_image(game.mlx, "textures/wall_1.xpm", &x, &y);
    game.win = mlx_new_window(game.mlx, winWidth, winHeight, "CUB3D");

    void *img = mlx_xpm_file_to_image(game.mlx, "textures/bg2.xpm", &x, &y);
    game.floor = img;
    game.wall = mlx_xpm_file_to_image(game.mlx, "textures/wall.xpm", &x, &y);
    drawMap(&game);
    mlx_hook(game.win, 02, 1L << 0, &movePlayer, &game);
    mlx_loop(game.mlx);
}