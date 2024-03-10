/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:29:27 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 13:17:16 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	h_raycast(const t_data *data, t_coordinates *endPoint, t_render *r)
{
	t_coordinates	step;
	float			scale;

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
	while (is_map(data, endPoint->x, endPoint->y)
		&& data->map.map[(int)endPoint->y][(int)endPoint->x] != WALL)
	{
		endPoint->x += step.x;
		endPoint->y += step.y;
	}
}

static void	v_raycast(const t_data *data, t_coordinates *endPoint, t_render *r)
{
	t_coordinates	step;
	float			scale;

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
	while (is_map(data, endPoint->x, endPoint->y)
		&& data->map.map[(int)endPoint->y][(int)endPoint->x] != WALL)
	{
		endPoint->x += step.x;
		endPoint->y += step.y;
	}
}

static void	find_hit(t_data *data, t_render *r,
	t_coordinates vEnd, t_coordinates hEnd)
{
	t_coordinates	ray_len;

	v_raycast(data, &vEnd, r);
	h_raycast(data, &hEnd, r);
	ray_len.x = sqrt(pow((data->player.pos.x + 0.5) - vEnd.x, 2)
			+ pow((data->player.pos.y + 0.5) - vEnd.y, 2));
	ray_len.y = sqrt(pow((data->player.pos.x + 0.5) - hEnd.x, 2)
			+ pow((data->player.pos.y + 0.5) - hEnd.y, 2));
	if (ray_len.x < ray_len.y)
	{
		r->distance = ray_len.x * cos(r->angle - data->player.angle);
		r->wall_hit = vEnd;
		r->y_tex = vEnd.y - (int)vEnd.y;
		r->direction = 'v';
	}
	else
	{
		r->distance = ray_len.y * cos(r->angle - data->player.angle);
		r->wall_hit = hEnd;
		r->y_tex = hEnd.x - (int)hEnd.x;
		r->direction = 'h';
	}
}

void	ft_render(t_data *data)
{
	t_render	r;
	int			i;
	float		rang;

	i = 0;
	rang = data->player.angle
		- (((float)((float)FOV * (float)PI / 180.0f)) / 2.0f);
	while (i < WIDTH)
	{
		r.angle = fmod(rang + ((float)i * ANGLE_RAD), 2.0f * PI);
		find_hit(data, &r, (t_coordinates){0, 0}, (t_coordinates){0, 0});
		r.wall_height = (HEIGHT / (1.5f * r.distance));
		ft_draw_wall(data, &r, i);
		i++;
	}
}
