/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:09:43 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 15:01:12 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int	ft_assign_aspect(t_data *data, t_img *img, char *sp)
{
	img->img = mlx_xpm_file_to_image(data->mlx.display_connector,
			sp, &img->width, &img->height);
	if (!img->img)
		return (printf("Error\nInvalid texture path : [%s].\n", sp), 0);
	img->get_addr = (int *)mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->steps);
	return (1);
}

static int	ft_assign_sprite(t_data *data, t_i_spr *spr, char **sp)
{
	int	i;
	int	len;

	len = ft_matrix_len((void **)sp);
	spr->img = (t_img *)ft_calloc(len + 1, sizeof(t_img));
	if (!spr->img)
		return (printf("Error\nMalloc failed.\n"), 0);
	spr->frames = len;
	i = -1;
	while (++i < len)
	{
		if (ft_assign_aspect(data, &spr->img[i], sp[i]) == 0)
			return (0);
	}
	return (1);
}

static int	ft_assign_color(int *color, char **sp)
{
	char	**rgb;
	int		rgb_val[3];

	rgb = ft_split(sp[1], ',');
	if (ft_matrix_len((void **)rgb) != 3)
		return (printf("Error\nInvalid color format [%s].\n", sp[1]), 0);
	if (!ft_is_number(rgb[0]) || !ft_is_number(rgb[1]) || !ft_is_number(rgb[2]))
		return (printf("Error\nInvalid color values [%s].\n", sp[1]), 0);
	rgb_val[0] = ft_atoi(rgb[0]);
	rgb_val[1] = ft_atoi(rgb[1]);
	rgb_val[2] = ft_atoi(rgb[2]);
	ft_free_matrix((void **)rgb);
	if (rgb_val[0] < 0 || rgb_val[0] > 255 || rgb_val[1] < 0 || rgb_val[1] > 255
		|| rgb_val[2] < 0 || rgb_val[2] > 255)
		return (printf("Error\nInvalid color values [%s].\n", sp[1]), 0);
	*color = ft_create_color(0, rgb_val[0], rgb_val[1], rgb_val[2]);
	return (1);
}

int	ft_assign_texture(t_data *data, char **sp)
{
	if (ft_strcmp(sp[0], "NO") == 0)
		return (ft_assign_aspect(data, &data->map.north, sp[1]));
	else if (ft_strcmp(sp[0], "SO") == 0)
		return (ft_assign_aspect(data, &data->map.south, sp[1]));
	else if (ft_strcmp(sp[0], "WE") == 0)
		return (ft_assign_aspect(data, &data->map.west, sp[1]));
	else if (ft_strcmp(sp[0], "EA") == 0)
		return (ft_assign_aspect(data, &data->map.east, sp[1]));
	else if (ft_strcmp(sp[0], "F") == 0)
		return (ft_assign_color(&data->map.floor_c, sp));
	else if (ft_strcmp(sp[0], "C") == 0)
		return (ft_assign_color(&data->map.ceiling_c, sp));
	else if (ft_strcmp(sp[0], "CO") == 0)
		return (ft_assign_sprite(data, &data->map.collec, &sp[1]));
	else if (ft_strcmp(sp[0], "DO") == 0)
		return (ft_assign_sprite(data, &data->map.door, &sp[1]));
	return (printf("Error\nInvalid texture information [%s].\n", sp[0]), 0);
}
