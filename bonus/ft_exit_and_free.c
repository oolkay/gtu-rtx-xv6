/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:03:15 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 12:03:16 by omer/baha        ###   ########.fr       */
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

static void	ft_free_images(t_data *data)
{
	ft_free_image(data, &data->mlx.img);
	ft_free_image(data, &data->minimap);
	ft_free_image(data, &data->map.north);
	ft_free_image(data, &data->map.south);
	ft_free_image(data, &data->map.east);
	ft_free_image(data, &data->map.west);
}

int	ft_free_and_exit(t_data *data, int status)
{
	ft_clear_window(data);
	ft_free_images(data);
	ft_free_matrix((void **)data->map.map);
	exit(status);
}
