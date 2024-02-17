#include "cub3d.h"

#define CELL_SIZE 64


static int isInMap(int **map, double x, double y)
{
    if (x < 0 || x / 64 > MAP_WIDTH)
        return 0;
    if (y < 0 || y / 64 > MAP_HEIGHT)
        return 0;
    return 1;
}

static int isHitWall(int **map, double x, double y)
{
    if (map[(int)y/64][(int)x/64] == 1)
        return 1;
    return 0;
}

static void horizontalRayCast(const t_game *game, t_fVector *endPoint, double angle)
{
    t_fVector step;
    float     scale;

    step.y = CELL_SIZE;
    if (sin(angle) > 0)
        endPoint->y = (int)(game->pl.y + 8) / 64 * 64 + 64;
    else
    {
        endPoint->y = (int)(game->pl.y + 8) / 64 * 64 - 0.0001;
        step.y *= -1;
    }
    step.x = step.y / tan(angle);
    scale = fabs((endPoint->y - (game->pl.y + 8)) / tan(angle));
    if (cos(angle) > 0)
        endPoint->x = game->pl.x + 8 + scale;
    else
        endPoint->x = game->pl.x + 8 - scale;
    while (isInMap(game->map, endPoint->x, endPoint->y)
        && !isHitWall(game->map, endPoint->x, endPoint->y))
    {
        endPoint->x += step.x;
        endPoint->y += step.y;
    }
}

static void verticalRayCast(const t_game *game, t_fVector *endPoint, double angle)
{
    t_fVector step;
    float     scale;

    step.x = CELL_SIZE;
    if (cos(angle) > 0)
        endPoint->x = (int)(game->pl.x + 8) / 64 * 64 + 64;
    else
    {
        endPoint->x = (int)(game->pl.x + 8) / 64 * 64 - 0.0001;
        step.x *= -1;
    }
    step.y = step.x * tan(angle);
    scale = fabs((endPoint->x - (game->pl.x + 8)) * tan(angle));
    if (sin(angle) > 0)
        endPoint->y = game->pl.y + 8 + scale;
    else
        endPoint->y = game->pl.y + 8 - scale;
    while (isInMap(game->map, endPoint->x, endPoint->y)
        && !isHitWall(game->map, endPoint->x, endPoint->y))
    {
        endPoint->x += step.x;
        endPoint->y += step.y;
    }
}

void rayCasting(const t_game *game, t_fVector *endPoint, double angle)
{
    t_fVector vEndPoint;
    t_fVector hEndPoint;
    double  vRayLen;
    double  hRayLen;

    verticalRayCast(game, &vEndPoint, angle);
    horizontalRayCast(game, &hEndPoint, angle);
    vRayLen = sqrt(pow(game->pl.x + 8 - vEndPoint.x, 2)
                    + pow(game->pl.y + 8 - vEndPoint.y, 2));
    hRayLen = sqrt(pow(game->pl.x + 8 - hEndPoint.x, 2)
                    + pow(game->pl.y + 8 - hEndPoint.y, 2));
    if (vRayLen < hRayLen)
    {
        endPoint->x = vEndPoint.x;
        endPoint->y = vEndPoint.y;
    }
    else
    {
        endPoint->x = hEndPoint.x;
        endPoint->y = hEndPoint.y;
    }
}