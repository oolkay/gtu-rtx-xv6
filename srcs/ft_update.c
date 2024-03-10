/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:45:02 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 13:19:24 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_draw_banner(t_data *data)
{
	mlx_string_put(data->mlx.display_connector, data->mlx.win,
		10, 10, 0xFFFFFF, "OOLKAY & ACEPNI");
	mlx_string_put(data->mlx.display_connector, data->mlx.win,
		WIDTH - 70, 10, 0xFFFFFF, "GTU-RTX-XV6");
}

int	ft_update(t_data *data)
{
	ft_move_player(data);
	ft_render(data);
	mlx_put_image_to_window(data->mlx.display_connector,
		data->mlx.win, data->mlx.img.img, 0, 0);
	ft_draw_banner(data);
	return (0);
}
