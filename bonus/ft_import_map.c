/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_import_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:08:37 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 18:45:49 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void	ft_init_map(t_map *map)
{
	map->north.img = NULL;
	map->south.img = NULL;
	map->west.img = NULL;
	map->east.img = NULL;
	map->ceiling_c = F_C_COLOR_DEF;
	map->floor_c = F_C_COLOR_DEF;
	map->map = NULL;
}

static void	ft_get_player_ang(t_data *data, double x, double y)
{
	if (data->map.map[(int)y][(int)x] == 'N')
		data->player.angle = 3 * PI / 2;
	else if (data->map.map[(int)y][(int)x] == 'S')
		data->player.angle = PI / 2;
	else if (data->map.map[(int)y][(int)x] == 'W')
		data->player.angle = PI;
	else if (data->map.map[(int)y][(int)x] == 'E')
		data->player.angle = 0;
}

static void	ft_init_player_starting_pos(t_data *data)
{
	int	i[2];

	ft_fill_garbage(i, 2);
	while (data->map.map[i[0]])
	{
		i[1] = 0;
		while (data->map.map[i[0]][i[1]])
		{
			if (ft_strchr("NSEW", data->map.map[i[0]][i[1]]))
			{
				data->player.pos.x = (double)i[1];
				data->player.pos.y = (double)i[0];
				ft_get_player_ang(data, data->player.pos.x, data->player.pos.y);
				return ;
			}
			i[1]++;
		}
		i[0]++;
	}
}

int	ft_import_map(t_data *data, char *argv)
{
	int	fd;
	int	return_value;

	ft_init_map(&data->map);
	if (ft_extention_check(argv) == 0)
		return (printf("Error\nInvalid file extension.\n./cub3d <file.cub>\n"),
			0);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nCouldn't open <%s> file.\n", argv), 0);
	return_value = ft_fill_textures(data, fd);
	if (return_value == 0)
		return (0);
	return_value = ft_parse_map(&data->map, fd);
	if (return_value == 0)
		return (0);
	ft_init_player_starting_pos(data);
	close(fd);
	return (1);
}
