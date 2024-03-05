/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall_desion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:38:56 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/19 14:42:15 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

static	t_coordinates	ft_y_point(t_coordinates pos, double angle)
{
	t_coordinates	tmp;

	tmp.x = floor(pos.x);
	if (angle > M_PI_2 && angle < 3 * M_PI_2)
		tmp.x += 1;
	else
		tmp.x -= 0.00000000001;
	tmp.y = pos.y + (tan(angle) * (tmp.x - pos.x));
	return (tmp);
}

static	t_coordinates	ft_x_point(t_coordinates pos, double angle)
{
	t_coordinates	tmp;

	tmp.y = floor(pos.y);
	if (angle > M_PI)
		tmp.y += 1;
	else
		tmp.y -= 0.00000000001;
	tmp.x = pos.x + (tmp.y - pos.y) / tan(angle);
	return (tmp);
}

static t_coordinates	ft_get_intersection_point(t_data *data,
	t_coordinates start, double angle,
	t_coordinates (*point)(t_coordinates, double))
{
	int				height;
	t_coordinates	start_inter;
	t_coordinates	delta;

	height = ft_matrix_len((void **)data->map.map);
	start_inter = point(start, angle);
	delta = point(start_inter, angle);
	delta.x -= start_inter.x;
	delta.y -= start_inter.y;
	while ((start_inter.x || start_inter.y)
		&& start_inter.x > 0 && start_inter.y > 0
		&& start_inter.y < height
		&& start_inter.x < (int)ft_strlen(data->map.map[(int)start_inter.y])
		&& !ft_strchr("1",
			data->map.map[(int)start_inter.y][(int)start_inter.x]))
	{
		start_inter.x += delta.x;
		start_inter.y += delta.y;
	}
	return (start_inter);
}

t_coordinates	ft_wall_hit(t_data *data,
	t_coordinates pos, double angle, int *dir)
{
	t_coordinates	x_intersection_p;
	t_coordinates	y_intersection_p;

	x_intersection_p = ft_get_intersection_point(data, pos, angle, &ft_x_point);
	y_intersection_p = ft_get_intersection_point(data, pos, angle, &ft_y_point);
	if (ft_distance(pos, x_intersection_p) < ft_distance(pos, y_intersection_p))
	{
		if (dir)
			*dir = 'h';
		return (x_intersection_p);
	}
	if (dir)
		*dir = 'v';
	return (y_intersection_p);
}

void	ft_wall_dimension(t_data *data, t_render *render,
	t_coordinates pos, double degree)
{
	render->degree = degree;
	render->wall_hit = ft_wall_hit(data, pos,
			render->angle, &render->direction);
	render->distance = ft_distance(data->player.pos,
			render->wall_hit)
		* cos(ft_update_radian(data->player.angle, -render->angle));
	render->wall_dimen.width = WIDTH / (FOV / ROT_SPEED);
	if (render->distance > 0)
		render->wall_dimen.height = HEIGHT / render->distance;
	render->wall_height = render->wall_dimen.height;
	if (render->wall_dimen.height > HEIGHT)
		render->wall_dimen.height = HEIGHT;
}
