/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:37:44 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/02 17:12:20 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void find_hit(t_data *data, t_render *r);
static void verticalRayCast(const t_data *data, t_coordinates *endPoint, t_render *r);
static void horizontalRayCast(const t_data *data, t_coordinates *endPoint, t_render *r);

static void ft_draw_floor_and_ceiling(t_data *data)
{
	int coordinates[2];

	ft_fill_garbage(coordinates, 2);
	while (coordinates[1] < HEIGHT)
	{
		coordinates[0] = 0;
		while (coordinates[0] < WIDTH)
		{
			if (coordinates[1] < HEIGHT / 2 && !data->mlx.img.get_addr[coordinates[1] * WIDTH + coordinates[0]])
				data->mlx.img.get_addr
					[coordinates[1] * WIDTH + coordinates[0]] = data->map.ceiling_c;
			else if (!data->mlx.img.get_addr[coordinates[1] * WIDTH + coordinates[0]])
				data->mlx.img.get_addr
					[coordinates[1] * WIDTH + coordinates[0]] = data->map.floor_c;
			coordinates[0]++;
		}
		coordinates[1]++;
	}
}

void	ft_render(t_data *data)
{
	t_render	r;
	int i = 0;
	float rang = data->player.angle - (((float)(FOV * PI / 180)) / 2);
	while (i < WIDTH)
	{
		r.angle = rang + ((float)i * ANGLE_RAD);
		find_hit(data, &r);
		r.wall_height = HEIGHT / r.distance;
		ft_draw_wall(data, &r, i);
		i++;
	}
}

static void find_hit(t_data *data, t_render *r)
{
	t_coordinates vEndPoint;
    t_coordinates hEndPoint;
    float vRayLen;
    float hRayLen;

    verticalRayCast(data, &vEndPoint, r);
	horizontalRayCast(data, &hEndPoint, r);

	vRayLen = sqrt(pow((data->player.pos.x + 0.5) - vEndPoint.x, 2) + pow((data->player.pos.y + 0.5) - vEndPoint.y, 2));
	hRayLen = sqrt(pow((data->player.pos.x + 0.5) - hEndPoint.x, 2) + pow((data->player.pos.y + 0.5) - hEndPoint.y, 2));

    if (vRayLen < hRayLen)
    {
        r->distance = vRayLen * fabs(cos(r->angle - data->player.angle));
        r->y_tex = vEndPoint.y - (int)vEndPoint.y;
    }
    else
    {
		r->distance = hRayLen * fabs(cos(r->angle - data->player.angle));
		r->y_tex = hEndPoint.x - (int)hEndPoint.x;
    }
}

static int isInMap(const t_data *data, float x, float y)
{
    if (y < 0 || y > ft_matrix_len((void **)data->map.map))
		return 0;
	if (x < 0 || x > ft_strlen(data->map.map[(int)y]))
		return 0;
    return 1;
}

static void horizontalRayCast(const t_data *data, t_coordinates *endPoint, t_render *r)
{
    t_coordinates step; // En yakın kesişimi bulduktan sonra eklenecek olan x ve y
    float scale;

	step.y = 1;
	if(sin(r->angle) > 0)
		endPoint->y = (int)(data->player.pos.y + 0.5) + 1;
	else
	{
		endPoint->y = (int)(data->player.pos.y + 0.5) - 0.0001;
		step.y *= -1;
	}
	scale = fabs(((endPoint->y - (data->player.pos.y + 0.5)) / tan(r->angle)));
	step.x = step.y / tan(r->angle);
	if (cos(r->angle) > 0)
		endPoint->x = data->player.pos.x + 0.5 + scale;
	else
		endPoint->x = data->player.pos.x + 0.5 - scale;
	while (isInMap(data, endPoint->x, endPoint->y) && data->map.map[(int)endPoint->y][(int)endPoint->x] != WALL)
	{
		endPoint->x += step.x;
		endPoint->y += step.y;
	}
}

static void verticalRayCast(const t_data *data, t_coordinates *endPoint, t_render *r)
{
	t_coordinates step;
	float scale;

	step.x = 1;
	if (cos(r->angle) > 0)
		endPoint->x = (int)(data->player.pos.x + 0.5) + 1;
	else
	{
		endPoint->x = (int)(data->player.pos.x + 0.5) - 0.0001;
		step.x *= -1;
	}
	step.y = step.x * tan(r->angle);
	scale = fabs(((endPoint->x - (data->player.pos.x + 0.5)) * tan(r->angle)));
	if (sin(r->angle) > 0)
		endPoint->y = data->player.pos.y + 0.5 + scale;
	else
		endPoint->y = data->player.pos.y + 0.5 - scale;
	while (isInMap(data, endPoint->x, endPoint->y) && data->map.map[(int)endPoint->y][(int)endPoint->x] != WALL)
	{
		endPoint->x += step.x;
		endPoint->y += step.y;
	}
}

// static void verticalRayCast(const t_game *game, t_dVector *endPoint, float angle)
// {
//     t_dVector step;
//     float scale;

//     step.x = CELL_SIZE;
//     if (cos(angle) > 0)
//         endPoint->x = (int)(game->pl.x + 8) / 64 * 64 + 64;
//     else
//     {
//         endPoint->x = (int)(game->pl.x + 8) / 64 * 64 - 0.0001;
//         step.x *= -1;
//     }
//     step.y = step.x * tan(angle);
//     scale = fabs((endPoint->x - (game->pl.x + 8)) * tan(angle));
//     if (sin(angle) > 0)
//         endPoint->y = game->pl.y + 8 + scale;
//     else
//         endPoint->y = game->pl.y + 8 - scale;
//     while (isInMap(game->map.arr, endPoint->x, endPoint->y) && !isHitWall(game->map.arr, endPoint->x, endPoint->y))
//     {
//         endPoint->x += step.x;
//         endPoint->y += step.y;
//     }
// }

// void	ft_render(t_data *data, double degree)
// {
// 	t_render	*r;
// 	t_list		*ll_render;

// 	printf("player x and y: %f %f\n", data->player.pos.x, data->player.pos.y);
// 	ll_render = NULL;
// 	while (degree <= FOV)
// 	{
// 		while (!ll_render || (ll_render && data->map.map
// 				[(int)((t_render *)(ll_render->data))->wall_hit.y]
// 				[(int)((t_render *)(ll_render->data))->wall_hit.x] != WALL))
// 		{
// 			r = malloc(1 * sizeof(t_render));
// 			r->angle = ft_update_radian(data->player.angle,
// 					ft_deg_to_rad(degree - (FOV / 2.0)));
// 			if (!ll_render)
// 				ft_wall_dimension(data, r, data->player.pos, degree);
// 			else
// 				ft_wall_dimension(data, r,
// 					((t_render *)(ll_render->data))->wall_hit, degree);
// 			ll_add_head(&ll_render, ll_new(r));
// 		}
// 		ft_draw_wall(data, ll_render);
// 		ft_ll_clear(&ll_render);
// 		degree += ROT_SPEED;
// 	}
// 	ft_draw_floor_and_ceiling(data);
// }