/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:44 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 15:01:12 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

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

static	void	ft_draw_pixel(t_data *data, int x, int y, t_render *render)
{
	t_img	*img;
	int		color;

	if (ft_strchr(DOORS, data->map.map[(int)(render->wall_hit.y)]
		[(int)(render->wall_hit.x)]))
	{
		img = &data->map.door.img[ft_ll_find(data->map.ll_door,
				render->wall_hit.x, render->wall_hit.y)];
	}
	else if (render->direction == 'h' && render->angle < M_PI)
		img = &data->map.north;
	else if (render->direction == 'h' && render->angle < 2.0 * M_PI)
		img = &data->map.south;
	else if (render->direction == 'v'
		&& (render->angle < M_PI_2 || render->angle > M_PI_2 * 3.0))
		img = &data->map.west;
	else
		img = &data->map.east;
	color = ft_get_pixel_texture(*img, render);
	if (color != ft_create_color(255, 0, 0, 0))
		data->mlx.img.get_addr[y * WIDTH + x] = color;
	if (ft_strchr(WALLS, data->map.map[(int)(render->wall_hit.y)]
		[(int)(render->wall_hit.x)]))
		data->map.depth[x] = render->distance;
}

void	ft_draw_wall(t_data *data, t_list *ll_render)
{
	int			x;
	int			y;
	t_render	*render;

	while (ll_render)
	{
		render = ll_render->data;
		render->y_tex = 0;
		y = (HEIGHT / 2) - (render->wall_dimen.height / 2);
		while (y < (HEIGHT / 2) + (render->wall_dimen.height / 2) && y < HEIGHT)
		{
			x = (render->degree / ROT_SPEED) * render->wall_dimen.width;
			while (x < ((render->degree / ROT_SPEED) * render->wall_dimen.width)
				+ render->wall_dimen.width && x < WIDTH)
			{
				ft_draw_pixel(data, x, y, render);
				x++;
			}
			(render->y_tex)++;
			y++;
		}
		ll_render = ll_render->next;
	}
}
