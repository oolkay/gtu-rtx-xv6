/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:34:56 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 15:01:12 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void	ft_clear_window(t_data *data)
{
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.display_connector, data->mlx.win);
}

static void	ft_free_image(t_data *data, t_img *image)
{
	if (image->img)
		mlx_destroy_image(data->mlx.display_connector, image->img);
}

static void	ft_free_sprites(t_data *data, t_i_spr *spr)
{
	int	i;

	i = -1;
	while (++i < spr->frames)
	{
		ft_free_image(data, &spr->img[i]);
	}
	if (spr->img)
		free(spr->img);
}

static void	ft_free_images(t_data *data)
{
	ft_free_image(data, &data->mlx.img);
	ft_free_image(data, &data->map.north);
	ft_free_image(data, &data->map.south);
	ft_free_image(data, &data->map.east);
	ft_free_image(data, &data->map.west);
	ft_free_sprites(data, &data->map.collec);
	ft_free_sprites(data, &data->map.door);
}

int	ft_free_and_exit(t_data *data, int status)
{
	ft_clear_window(data);
	ft_free_images(data);
	ft_ll_clear(&data->map.ll_collect);
	ft_ll_clear(&data->map.ll_door);
	ft_free_matrix((void **)data->map.map);
	exit(status);
}
