/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:55:57 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 15:01:12 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int	ft_is_filled(t_map *map)
{
	if (map->north.img && map->south.img && map->west.img && map->east.img
		&& map->collec.img && map->door.img
		&& map->floor_c != F_C_COLOR_DEF && map->ceiling_c != F_C_COLOR_DEF)
		return (1);
	return (0);
}

static int	ft_format_check(char **sp)
{
	int	len;

	len = ft_matrix_len((void **)sp);
	if ((ft_strcmp(sp[0], "NO") == 0 && len != 2)
		|| (ft_strcmp(sp[0], "SO") == 0 && len != 2)
		|| (ft_strcmp(sp[0], "WE") == 0 && len != 2)
		|| (ft_strcmp(sp[0], "EA") == 0 && len != 2)
		|| (ft_strcmp(sp[0], "CO") == 0 && len < 2)
		|| (ft_strcmp(sp[0], "DO") == 0 && len < 2)
		|| (ft_strcmp(sp[0], "F") == 0 && len != 2)
		|| (ft_strcmp(sp[0], "C") == 0 && len != 2))
		return (printf("Error\nInvalid texture format [%s].\n", sp[0]), 0);
	return (1);
}

static int	ft_dup_check(t_data *data, char **sp)
{
	if ((ft_strcmp(sp[0], "NO") == 0 && data->map.north.img)
		|| (ft_strcmp(sp[0], "SO") == 0 && data->map.south.img)
		|| (ft_strcmp(sp[0], "WE") == 0 && data->map.west.img)
		|| (ft_strcmp(sp[0], "EA") == 0 && data->map.east.img)
		|| (ft_strcmp(sp[0], "CO") == 0 && data->map.collec.img)
		|| (ft_strcmp(sp[0], "DO") == 0 && data->map.door.img)
		|| (ft_strcmp(sp[0], "F") == 0 && data->map.floor_c != F_C_COLOR_DEF)
		|| (ft_strcmp(sp[0], "C") == 0 && data->map.ceiling_c != F_C_COLOR_DEF))
		return (printf("Error\nDuplicated texture [%s].\n", sp[0]), 0);
	return (1);
}

static int	ft_parse_textures(t_data *data, char **sp)
{
	int	return_value;

	return_value = ft_format_check(sp);
	if (!return_value)
		return (0);
	return_value = ft_dup_check(data, sp);
	if (!return_value)
		return (0);
	return_value = ft_assign_texture(data, sp);
	if (!return_value)
		return (0);
	return (return_value);
}

int	ft_fill_textures(t_data *data, int fd)
{
	char	*line;
	char	**line_sp;
	int		return_value;

	while (ft_is_filled(&data->map) == 0)
	{
		line = get_next_line(fd);
		if (!line)
			return (printf("Error\nInvalid map.\nMissing textures.\n"), 0);
		else if (*line)
		{
			line_sp = ft_split(line, ' ');
			if (!line_sp)
				return (printf("Error\nMalloc failed\nMap cannot splitted!"), 0);
			return_value = ft_parse_textures(data, line_sp);
			if (!return_value)
				return (ft_free_matrix((void **)line_sp), free(line), 0);
			ft_free_matrix((void **)line_sp);
		}
		free(line);
	}
	return (1);
}
