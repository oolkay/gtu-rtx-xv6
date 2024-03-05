/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 13:23:02 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 15:01:12 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void	ft_collec_ani(t_data *data, t_object *c)
{
	double	new_frame;

	new_frame = c->frame + COLLECT_FRAME;
	if ((int)new_frame < data->map.collec.frames)
		c->frame = new_frame;
	else
		c->frame = 0;
}

static int	ft_is_in_bound(t_data *data, t_object *temp, int x)
{
	t_coordinates	coord;

	coord.x = (double)temp->x + OFF_SET;
	coord.y = (double)temp->y + OFF_SET;
	if (ft_distance(data->player.pos, coord) < data->map.depth[x])
		return (1);
	return (0);
}

static void	ft_draw_sprite(t_data *data,
	t_sprite *r, t_img *img, t_object *temp)
{
	int	i;
	int	j;
	int	c;

	i = r->screen.x - 1;
	while (++i < r->screen.x + r->sprite.width && i < WIDTH)
	{
		j = r->screen.y;
		while (i >= 0 && j < r->screen.y + r->sprite.height && j < HEIGHT
			&& ft_is_in_bound(data, temp, i))
		{
			r->textures.x = (i - r->screen.x) * (img->width / r->sprite.width);
			r->textures.y = (j - r->screen.y)
				* (img->height / r->sprite.height);
			if (j >= 0 && r->textures.x >= 0 && r->textures.x < img->width
				&& r->textures.y >= 0 && r->textures.y < img->height)
			{
				c = img->get_addr
				[(int)r->textures.y * img->width + (int)r->textures.x];
				if (c != ft_create_color(255, 0, 0, 0))
					data->mlx.img.get_addr[j * WIDTH + i] = c;
			}
			j++;
		}
	}
}

static void	ft_sprites_helper(t_sprite *spr, t_object *temp, t_data *data)
{
	spr->collecs.x = (double)temp->x + OFF_SET;
	spr->collecs.y = (double)temp->y + OFF_SET;
	spr->screen.x = data->player.pos.x - spr->collecs.x;
	spr->screen.y = data->player.pos.y - spr->collecs.y;
}

void	ft_sprites(t_data *data)
{
	t_sprite	spr;
	t_list		*head;
	t_object	*temp;
	double		angle;

	head = data->map.ll_collect;
	while (head)
	{
		temp = head->data;
		ft_sprites_helper(&spr, temp, data);
		ft_collec_ani(data, temp);
		angle = ft_update_radian(data->player.angle,
				ft_deg_to_rad(FOV / 2.0)
				- atan2(spr.screen.y, spr.screen.x));
		spr.sprite.height = (HEIGHT / 2) / ft_distance(data->player.pos,
				spr.collecs);
		spr.sprite.width = spr.sprite.height;
		spr.screen.x = WIDTH
			- ((angle * WIDTH / ft_deg_to_rad(FOV)) + (spr.sprite.width / 2));
		spr.screen.y = HEIGHT / 2;
		ft_draw_sprite(data, &spr,
			&data->map.collec.img[(int)temp->frame], temp);
		head = head->next;
	}
}
