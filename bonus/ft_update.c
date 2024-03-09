/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acepni <acepni@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:13:14 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/09 18:39:41 by acepni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"


int ft_update(t_data *data)
{
	ft_move_player(data);
	ft_draw_minimap(data);
	ft_render(data);
	// mlx_clear_window(data->mlx.display_connector, data->mlx.win);
	mlx_put_image_to_window(data->mlx.display_connector,
							data->mlx.win, data->mlx.img.img, 0, 0);
    mlx_put_image_to_window(data->mlx.display_connector,
							data->mlx.win, data->minimap.img, WIDTH-250, HEIGHT-250);
	return (0);
}
