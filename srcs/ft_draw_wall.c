/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:31:41 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 14:30:15 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_get_pixel_texture(t_img image, t_render *render)
{
	int		tx;
	int		ty;
	double	ty_step;
	double	ty_off;

	if (render->direction == 'h')
		tx = image.width * (render->wall_hit.x - (int)(render->wall_hit.x));
	else
		tx = image.width * (render->wall_hit.y - (int)(render->wall_hit.y));
	ty_step = image.height / render->wall_height;
	ty_off = 0;
	if (render->wall_height > HEIGHT)
		ty_off = (render->wall_height - HEIGHT) / 2;
	ty = (ty_off * ty_step) + ((render->y_tex) * ty_step);
	return (image.get_addr[(abs(ty) * image.width) + abs(tx)]);
}

static void	ft_draw_pixel(t_data *data, int x, int y, t_render *render)
{
	t_img	*img;
	int		color;

	img = NULL;
	if (render->direction == 'h' && (render->angle <= PI && render->angle >= 0))
	{
		img = &data->map.north;
	}
	else if (render->direction == 'h')
	{
		img = &data->map.south;
	}
	else if (render->direction == 'v' && (render->angle >= (PI / 2)
			&& render->angle <= (3 * PI / 2)))
		img = &data->map.west;
	else if (render->direction == 'v')
		img = &data->map.east;
	color = ft_get_pixel_texture(*img, render);
	data->mlx.img.get_addr[y * WIDTH + x] = color;
}

void	ft_draw_wall(t_data *data, t_render *render, int x)
{
	int	y;
	int	y_off;
	int	y_end;

	y_off = (HEIGHT / 2) - (render->wall_height / 2);
	y_end = (HEIGHT / 2) + (render->wall_height / 2) - 1;
	y = 0;
	while (y < y_off)
	{
		data->mlx.img.get_addr[y * WIDTH + x] = data->map.ceiling_c;
		y++;
	}
	while (y < y_end && y < HEIGHT)
	{
		ft_draw_pixel(data, x, y, render);
		(render->y_tex)++;
		y++;
	}
	while (y < HEIGHT)
	{
		data->mlx.img.get_addr[y * WIDTH + x] = data->map.floor_c;
		y++;
	}
}
