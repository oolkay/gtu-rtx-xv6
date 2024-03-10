/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:12:47 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 12:16:08 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void	ft_update_player_direction(t_data *data)
{
	double	angle;

	if (data->player.rotate)
		data->player.angle = ft_update_radian(data->player.angle,
				data->player.rotate * ROT_SPEED);
	angle = data->player.angle;
	if (data->player.move.y == 1)
		angle = ft_update_radian(angle, -PI);
	else if (data->player.move.x)
		angle = ft_update_radian(angle,
				data->player.move.x * PI / 2);
	if (data->player.move.y && data->player.move.x)
		angle = ft_update_radian(angle,
				data->player.move.x * PI / 4);
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
	if (!ft_strchr("1", data->map.map[(int)((data->player.pos.y + 0.5))]
		[(int)(new_pos.x + 0.5)]))
		data->player.pos.x = new_pos.x;
	new_pos.y = data->player.pos.y + data->player.dir.y * SPEED;
	if (!ft_strchr("1", data->map.map[(int)(new_pos.y + 0.5)]
		[(int)(data->player.pos.x + 0.5)]))
		data->player.pos.y = new_pos.y;
}
