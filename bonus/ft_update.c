/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:45:02 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 16:52:39 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void	ft_draw_rectangle(t_data *data, t_coordinates start,
	t_coordinates size, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			mlx_pixel_put(data->mlx.display_connector, data->mlx.win,
				start.x + x, start.y + y, color);
			x++;
		}
		y++;
	}
}

void	ft_draw_banner(t_data *data)
{
	mlx_string_put(data->mlx.display_connector, data->mlx.win,
		10, 10, 0xFFFFFF, "OOLKAY & ACEPNI");
	mlx_string_put(data->mlx.display_connector, data->mlx.win,
		WIDTH - 75, 10, 0xFFFFFF, "GTU-RTX-XV6");
	mlx_string_put(data->mlx.display_connector, data->mlx.win,
		WIDTH - 225, HEIGHT - 40, 0xFFFFFF, "Press F to toggle minimap");
    //crosshair 4 RECTANGLE
    ft_draw_rectangle(data, (t_coordinates){WIDTH / 2 - 10, HEIGHT/2 - 2}, (t_coordinates){6, 4}, GREEN);
    ft_draw_rectangle(data, (t_coordinates){WIDTH / 2 + 4, HEIGHT/2 - 2}, (t_coordinates){6, 4}, GREEN);
    ft_draw_rectangle(data, (t_coordinates){WIDTH / 2 - 2, HEIGHT / 2 - 10}, (t_coordinates){4, 6}, GREEN);
    ft_draw_rectangle(data, (t_coordinates){WIDTH / 2 - 2, HEIGHT / 2 + 4}, (t_coordinates){4, 6}, GREEN);
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
			WIDTH - (WIDTH / 3), HEIGHT - (HEIGHT / 3));
	ft_draw_banner(data);
	return (0);
}
