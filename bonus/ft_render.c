/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oolkay <oolkay@42.tr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:37:44 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/09 23:55:04 by oolkay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void find_hit(t_data *data, t_render *r);
static void verticalRayCast(const t_data *data, t_coordinates *endPoint, t_render *r);
static void horizontalRayCast(const t_data *data, t_coordinates *endPoint, t_render *r);

void ft_draw_rays(t_data *data, t_render *render, int i)
{
	double beginx = WIDTH / 8;
	double beginy = WIDTH / 8;
	t_coordinates offset;
	// t_coordinates endp;

	offset.x = render->wall_hit.x - (data->player.pos.x + 0.5);
	offset.y = render->wall_hit.y - (data->player.pos.y + 0.5);
	// endp.x = (offset.x * 20) + beginx;
	// endp.y = (offset.y * 20) + beginy;

	double step = fmax(fabs(offset.x), fabs(offset.y));
	offset.x /= step;
	offset.y /= step;
	int j = 0;
	step = step * (WIDTH / 40);
	while (j < step)
	{
		if (beginx > 0 && beginx < WIDTH / 4 - 1 && beginy > 0 && beginy < HEIGHT / 4 - 1)
			data->minimap.get_addr[(int)beginy * WIDTH / 4 + (int)beginx] = 0xFF00FF;
		beginx += offset.x;
		beginy += offset.y;
		j++;
	}
}

void ft_render(t_data *data)
{
	t_render r;
	int i = 0;
	float rang = data->player.angle - (((float)((float)FOV * (float)PI / 180.0f)) / 2.0f);
	while (i < WIDTH)
	{
		r.angle = fmod(rang + ((float)i * ANGLE_RAD), 2.0f * PI);
		// printf("angle: %f.2\n", r.angle);
		find_hit(data, &r);
		r.wall_height = (HEIGHT / (1.5f * r.distance));
		ft_draw_wall(data, &r, i);
		ft_draw_rays(data, &r, i);
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
		r->distance = vRayLen * cos(r->angle - data->player.angle);
		r->wall_hit = vEndPoint;
		r->y_tex = vEndPoint.y - (int)vEndPoint.y;
		r->direction = 'v';
	}
	else
	{
		r->distance = hRayLen * cos(r->angle - data->player.angle);
		r->wall_hit = hEndPoint;
		r->y_tex = hEndPoint.x - (int)hEndPoint.x;
		r->direction = 'h';
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
	if (sin(r->angle) > 0)
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
