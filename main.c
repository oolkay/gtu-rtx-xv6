#include "cub3d.h"
#include <unistd.h>
#include <math.h>

#define Macos 0

#define A 0
#define S 1
#define D 2
#define W 13

#define AL 97
#define SL 115
#define DL 100
#define WL 119

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
    game.img.i = mlx_new_image(game.mlx, winWidth, winHeight);
	game.img.addr = mlx_get_data_addr(game.img.i, &game.img.bpp, \
		&game.img.line_len, &game.img.endian);
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

static void fill_image(t_game *game, int color)
{
    int x = 0;
    int y = 0;
    while (y < winHeight)
    {
        x = 0;
        while (x < winWidth)
        {
            my_mlx_pixel_put(&game->img, x, y, color);
            x++;
        }
        y++;
    }
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


static void draw3Dline(t_game *game, int x1, int y2, int color)
{
    x1 = (winWidth / 2) + x1;
    for (int i = 0; i < y2 / 2; i++)
    {
        if (x1 < 0 || x1 > winWidth)
            break;
        if(winHeight / 2 + i < 0 || winHeight / 2 + i > winHeight)
            break;
        if(winHeight / 2 - i < 0 || winHeight / 2 - i > winHeight)
            break;
        my_mlx_pixel_put(&game->img, x1, winHeight / 2 + i, color);
        my_mlx_pixel_put(&game->img, x1, winHeight / 2 - i, color);
    }
}

static void drawLine(t_game *game, float angle, int ray_index)
{
    float beginx = game->pl.x + 16 / 2;
    float beginy = game->pl.y + 16 / 2;
    t_dVector endPoint;
    float endx = beginx;
    float endy = beginy;
    float dist = 0;

    float ang = angle;

    float dx, dy, x1, y1, x2, y2;
    float x0, y0;
    float distV, distH;

    rayCasting(game, &endPoint, &dist, angle);

    endx = endPoint.x;
    endy = endPoint.y;
    float x = beginx;
    float y = beginy;
    float step = fabs(endx - beginx);
    if (fabs(endy - beginy) > step)
        step = fabs(endy - beginy);
    float xInc = (endx - beginx) / step;
    float yInc = (endy - beginy) / step;
    for (int i = 0; i < step; i++)
    {
        my_mlx_pixel_put(&game->img, x, y, 0xff00ff);
        x += xInc;
        y += yInc;
    }

	float wall_height = (int)((winHeight * 50) / (dist));
    draw3Dline(game, ray_index, wall_height, 0xff00ff - powf(1.14, dist / 7));
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
            my_mlx_pixel_put(&game->img, game->pl.x + i, game->pl.y + j, 0xff0000);
        }
    }
    for (int i = 0; i < 16; ++i)
    {
        for (int j = 0; j < 16; j++)
        {
            my_mlx_pixel_put(&game->img, game->pl.x + i, game->pl.y + j, 0xff0000);
        }
    }
    for (int i = 0; i < (winWidth/2); i++)
    {
        drawLine(game, game->pl.angle - FOVrad + (float)(i * game->pl.angledrad), i);
    }
    draw3Dline(game, 22, 50, 0xffffff);
    mlx_put_image_to_window(game->mlx, game->win, game->img.i, 0, 0);
    return (1);
}

static int drawMap(t_game *game)
{
    my_mlx_area_put(&game->img, (t_dVector){winWidth/2, 0}, (t_dVector){winWidth, winHeight}, 0x0000ff);
    // mlx_put_image_to_window(game->mlx, game->win, game->bg, winWidth/2, 0);
    //mlx_img_to_img((int[2]){0, 0}, (t_img[2]){game->bg, &game->img}, 0x0000ff);
    for (int i = 0; i < MAP_HEIGHT; ++i)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            if (map[i][j] == 1)
            {
                my_mlx_area_put(&game->img, (t_dVector){j * 64, i * 64}, (t_dVector){64, 64}, 0x00ff00);
                // mlx_put_image_to_window(game->mlx, game->win, game->wall, j * 64, i * 64);
            }
            else
            {
                my_mlx_area_put(&game->img, (t_dVector){j * 64, i * 64}, (t_dVector){64, 64}, 0x0000ff);
                // mlx_put_image_to_window(game->mlx, game->win, game->floor, j * 64, i * 64);
            }
        }
    }
    for (int i = winWidth/2; i < winWidth; i++)
    return (1);
}

static int movePlayer(int keycode, void *_game)
{
    t_game *game = _game;
    if (keycode == ESC)
    {
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }
    if ((Macos && keycode == W) || (!Macos && keycode == WL))
    {
        game->pl.x += game->pl.dx;
        game->pl.y += game->pl.dy;
    }
    if ((Macos && keycode == S) || (!Macos && keycode == SL))
    {
        game->pl.x -= game->pl.dx;
        game->pl.y -= game->pl.dy;
    }
    if ((Macos && keycode == A) || (!Macos && keycode == AL))
    {
        game->pl.angle -= 0.1;
        if (game->pl.angle < 0)
            game->pl.angle += 2 * PI;
        game->pl.dx = lineLen * cos(game->pl.angle);
        game->pl.dy = lineLen * sin(game->pl.angle);
    }
    if ((Macos && keycode == D) || (!Macos && keycode == DL))
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

    mlx_put_image_to_window(game.mlx, game.win, game.img.i, 0, 0);

    // void *img = mlx_xpm_file_to_image(game.mlx, "textures/bg2.xpm",  &x, &y);
    // game.floor = img;
    game.wall = mlx_xpm_file_to_image(game.mlx, "textures/wall_1.xpm", &x, &y);
    game.bg = mlx_xpm_file_to_image(game.mlx, "textures/fc.xpm", &x, &y);
    // drawMap(&game);
    mlx_hook(game.win, 02, 1L << 0, &movePlayer, &game);
    mlx_loop(game.mlx);
}