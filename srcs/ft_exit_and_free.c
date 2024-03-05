/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 16:34:56 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 15:10:23 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
