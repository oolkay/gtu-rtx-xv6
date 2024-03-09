/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acepni <acepni@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:05:31 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/09 17:24:34 by acepni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

int ft_init_images(t_data *data)
{
	data->mlx.img.img = mlx_new_image(data->mlx.display_connector,
									  WIDTH, HEIGHT);
	if (!data->mlx.img.img)
		return (printf("Error\nCouldn't initilize window.\n"), 0);
	data->mlx.img.get_addr = (int *)mlx_get_data_addr(data->mlx.img.img,
													  &data->mlx.img.bits_per_pixel, &data->mlx.img.line_length,
													  &data->mlx.img.steps);

	data->minimap.img = mlx_new_image(data->mlx.display_connector,
									  WIDTH / 4, WIDTH / 4);
	if (!data->minimap.img)
		return (printf("Error\nCouldn't initilize minimap.\n"), 0);
	data->minimap.get_addr = (int *)mlx_get_data_addr(data->minimap.img,
													  &data->minimap.bits_per_pixel, &data->minimap.line_length,
													  &data->minimap.steps);
	data->map.show_minimap = 1;
	return (1);
}
