/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:11:34 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 21:42:18 by cbolat           ###   ########.fr       */
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
	if (data->player.move.y == -1)
		angle = ft_update_radian(angle, M_PI);
	else if (data->player.move.x)
		angle = ft_update_radian(angle,
				-data->player.move.x * M_PI_2);
	if (data->player.move.x && data->player.move.y)
	{
		angle = ft_update_radian(angle,
				data->player.move.x * M_PI_4);
	}
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
			data->map.map[(int)data->player.pos.y][(int)new_pos.x]))
		data->player.pos.x = new_pos.x;
	new_pos.y = data->player.pos.y + data->player.dir.y * SPEED;
	if (!ft_strchr("1",
			data->map.map[(int)new_pos.y][(int)data->player.pos.x]))
		data->player.pos.y = new_pos.y;
}
