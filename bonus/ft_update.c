/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:45:02 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 13:58:11 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

void	ft_draw_banner(t_data *data)
{
	mlx_string_put(data->mlx.display_connector, data->mlx.win,
		10, 10, 0xFFFFFF, "OOLKAY & ACEPNI");
	mlx_string_put(data->mlx.display_connector, data->mlx.win,
		WIDTH - 70, 10, 0xFFFFFF, "GTU-RTX-XV6");
	mlx_string_put(data->mlx.display_connector, data->mlx.win,
		WIDTH - 225, HEIGHT - 40, 0xFFFFFF, "Press F to toggle minimap");
}

int	ft_update(t_data *data)
{
	ft_move_player(data);
	ft_draw_minimap(data, 0, 0,
		(t_coordinates){data->player.pos.x + 0.5, data->player.pos.y + 0.5});
	ft_render(data);
	mlx_put_image_to_window(data->mlx.display_connector,
		data->mlx.win, data->mlx.img.img, 0, 0);
	if (data->map.show_minimap)
		mlx_put_image_to_window(data->mlx.display_connector,
			data->mlx.win, data->minimap.img,
			WIDTH - (WIDTH/3), HEIGHT - (HEIGHT/3));
	ft_draw_banner(data);
	return (0);
}
