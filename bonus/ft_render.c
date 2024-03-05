/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:37:44 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/02 17:11:42 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void	ft_draw_floor_and_ceiling(t_data *data)
{
	int	coordinates[2];

	ft_fill_garbage(coordinates, 2);
	while (coordinates[1] < HEIGHT)
	{
		coordinates[0] = 0;
		while (coordinates[0] < WIDTH)
		{
			if (coordinates[1] < HEIGHT / 2 && !data->mlx.img.get_addr[coordinates[1] * WIDTH + coordinates[0]])
				data->mlx.img.get_addr
				[coordinates[1] * WIDTH + coordinates[0]]
					= data->map.ceiling_c;
			else if (!data->mlx.img.get_addr[coordinates[1] * WIDTH + coordinates[0]])
				data->mlx.img.get_addr
				[coordinates[1] * WIDTH + coordinates[0]]
					= data->map.floor_c;
			coordinates[0]++;
		}
		coordinates[1]++;
	}
}

void	ft_render(t_data *data, double degree)
{
	t_render	*r;
	t_list		*ll_render;

	ll_render = NULL;
	while (degree <= FOV)
	{
		while (!ll_render || (ll_render && data->map.map
				[(int)((t_render *)(ll_render->data))->wall_hit.y]
				[(int)((t_render *)(ll_render->data))->wall_hit.x] != WALL))
		{
			r = malloc(1 * sizeof(t_render));
			r->angle = ft_update_radian(data->player.angle,
					ft_deg_to_rad(degree - (FOV / 2.0)));
			if (!ll_render)
				ft_wall_dimension(data, r, data->player.pos, degree);
			else
				ft_wall_dimension(data, r,
					((t_render *)(ll_render->data))->wall_hit, degree);
			ll_add_head(&ll_render, ll_new(r));
		}
		ft_draw_wall(data, ll_render);
		ft_ll_clear(&ll_render);
		degree += ROT_SPEED;
	}
	ft_draw_floor_and_ceiling(data);
}
