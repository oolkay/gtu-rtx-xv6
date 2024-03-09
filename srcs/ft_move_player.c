/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oolkay <oolkay@42.tr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:11:34 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/09 21:16:36 by oolkay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	ft_update_player_direction(t_data *data)
{
	double	angle;

	if (data->player.rotate)
		data->player.angle = ft_update_radian(data->player.angle, 
			data->player.rotate * ROT_SPEED);
	angle = data->player.angle;


	if (data->player.move.y == S_PRESSED)
		angle = ft_update_radian(angle, -PI);
	else if (data->player.move.x)
		angle = ft_update_radian(angle, 
			data->player.move.x * PI / 2);
	if (data->player.move.y && data->player.move.x)
		angle = ft_update_radian(angle, 
		-data->player.move.x * PI / 4);
	data->player.dir.x = cos(angle);
	data->player.dir.y = sin(angle);
}

void	ft_move_player(t_data *data)
{
	t_coordinates	new_pos;

	ft_update_player_direction(data);
	if (!(int)data->player.move.x && !(int)data->player.move.y)
		return ;
	new_pos.x = data->player.pos.x + data->player.dir.x * SPEED;
	if (!ft_strchr("1",
			data->map.map[(int)((data->player.pos.y + 0.5))][(int)(new_pos.x + 0.5)]))
		data->player.pos.x = new_pos.x;
	new_pos.y = data->player.pos.y + data->player.dir.y * SPEED;
	if (!ft_strchr("1",
			data->map.map[(int)(new_pos.y + 0.5)][(int)(data->player.pos.x + 0.5)]))
		data->player.pos.y = new_pos.y;
}

/*


	float	angle;

	angle = g->ray.angle;
	if (k == KEY_A)
		angle = g->ray.angle - 90;
	else if (k == KEY_S)
		angle = g->ray.angle - 180;
	else if (k == KEY_D)
		angle = g->ray.angle + 90;
	ray_cos = cos(degree_to_radians(angle)) * g->pl.speed;
	ray_sin = sin(degree_to_radians(angle)) * g->pl.speed;
	if (!ft_strchr("1c", g->map[(int)(g->pl.y + 0.5 + \
			(3 * ray_sin))][(int)(g->pl.x + 0.5)]))
		g->pl.y += ray_sin;
	if (!ft_strchr("1c", \
		g->map[(int)(g->pl.y + 0.5)][(int)(g->pl.x + 0.5 + (3 * ray_cos))]))
		g->pl.x += ray_cos;
		
*/