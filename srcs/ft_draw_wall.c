/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oolkay <oolkay@42.tr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:44 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/09 21:19:11 by oolkay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int ft_get_pixel_texture(t_img image, t_render *render)
{
	int tx;
	int ty;
	double ty_step;
	double ty_off;

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

static void ft_draw_pixel(t_data *data, int x, int y, t_render *render)
{
	t_img *img;
	int color;

	if (render->direction == 'h' && (render->angle <= PI && render->angle >= 0))
		{
			img = &data->map.north;}
	else if (render->direction == 'h')
		{
			img = &data->map.south;}
	else if (render->direction == 'v' && (render->angle >= (PI / 2) || render->angle <= (3 * PI / 2))) 
		img = &data->map.west;
	else if (render->direction == 'v')
		img = &data->map.east;
	color = ft_get_pixel_texture(*img, render);
	// if (color != ft_create_color(255, 0, 0, 0))
	data->mlx.img.get_addr[y * WIDTH + x] = color;
}

void ft_draw_wall(t_data *data, t_render *render, int x)
{
	int y;
	int y_off;
	int y_end;

	y_off = (HEIGHT / 2) - (render->wall_height / 2);
	y_end = (HEIGHT / 2) + (render->wall_height / 2);
	y = 0;
	while (y < y_off)
	{
		data->mlx.img.get_addr[y * WIDTH + x] = data->map.ceiling_c;
		y++;
	}
	while (y < y_end && y < HEIGHT)
	{
		// data->mlx.img.get_addr[y * WIDTH + x] = 0xFFAABB;
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

// void	ft_draw_wall(t_data *data, t_list *ll_render)
// {
// 	int			x;
// 	int			y;
// 	t_render	*render;

// 	while (ll_render)
// 	{
// 		render = ll_render->data;
// 		render->y_tex = 0;
// 		y = (HEIGHT / 2) - (render->wall_dimen.height / 2);
// 		for (int i = 0; i < y; i++)
// 		{
// 			x = (render->degree / ROT_SPEED) * render->wall_dimen.width;
// 			data->mlx.img.get_addr[i * WIDTH + x] = data->map.ceiling_c;
// 			data->mlx.img.get_addr[i * WIDTH + x + 1] = data->map.ceiling_c;
// 		}

// 		while (y < (HEIGHT / 2) + (render->wall_dimen.height / 2) && y < HEIGHT)
// 		{
// 			x = (render->degree / ROT_SPEED) * render->wall_dimen.width;
// 			while (x < ((render->degree / ROT_SPEED) * render->wall_dimen.width)
// 				+ render->wall_dimen.width && x < WIDTH){
// 				// if (!data->mlx.img.get_addr[y * WIDTH + x])
// 					ft_draw_pixel(data, x, y, render);
// 				x++;
// 			}
// 			(render->y_tex)++;
// 			y++;
// 		}
// 		for (int i = y; i < HEIGHT; i++)
// 		{
// 			x = (render->degree / ROT_SPEED) * render->wall_dimen.width;
// 			data->mlx.img.get_addr[i * WIDTH + x] = data->map.floor_c;
// 			data->mlx.img.get_addr[i * WIDTH + x + 1] = data->map.floor_c;

// 		}
// 		ll_render = ll_render->next;
// 	}
// }
