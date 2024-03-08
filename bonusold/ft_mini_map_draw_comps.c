/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_map_draw_comps.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:58:00 by alcelik           #+#    #+#             */
/*   Updated: 2023/08/20 15:01:12 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static void	ft_draw_square_comp(int *data, int color,
								t_coordinates cords, t_mini_map map)
{
	int	x;
	int	y;

	y = cords.y + 1;
	while (y < cords.y + MAP_EDGE_L - 1)
	{
		x = cords.x + 1;
		while (x < cords.x + MAP_EDGE_L - 1)
		{
			if (ft_is_in_map_bound(map, x, y) == 1)
				data[y * WIDTH + x] = color;
			x++;
		}
		y++;
	}
}

static void	ft_draw_comps_utils(t_data *data, t_mini_map map,
								t_coordinates cords, int *index)
{
	if (data->map.map[index[0]][index[1]] == CLOSED_DOOR)
		ft_draw_square_comp(data->mlx.img.get_addr,
			ft_create_color(0, 160, 40, 20), cords, map);
	else if (data->map.map[index[0]][index[1]] == COLLECS)
		ft_draw_square_comp(data->mlx.img.get_addr,
			ft_create_color(0, 20, 120, 55), cords, map);
	else if (!ft_strchr("03NSEW ", data->map.map[index[0]][index[1]]))
	{
		ft_draw_square_comp(data->mlx.img.get_addr,
			ft_create_color(0, 60, 60, 60), cords, map);
	}
}

void	ft_draw_comps(t_data *data, t_mini_map map)
{
	t_coordinates	cords;
	int				index[2];

	index[0] = ft_max(0, data->player.pos.y - (MAP_FOV / 2));
	while (data->map.map[index[0]]
		&& index[0] <= data->player.pos.y + (MAP_FOV / 2))
	{
		index[1] = ft_max(0, data->player.pos.x - MAP_FOV / 2);
		while (data->map.map[index[0]][index[1]]
		&& index[1] <= data->player.pos.x + (MAP_FOV / 2))
		{
			cords.y = (index[0] * MAP_EDGE_L)
				- (data->player.pos.y * MAP_EDGE_L) + CENTER;
			cords.x = (index[1] * MAP_EDGE_L)
				- (data->player.pos.x * MAP_EDGE_L) + CENTER;
			ft_draw_comps_utils(data, map, cords, index);
			index[1]++;
		}
		index[0]++;
	}
}

static void	ft_draw_mini_map_line(t_data *data,
								t_coordinates wall, t_mini_map map)
{
	int				steps;
	t_coordinates	inc;
	t_coordinates	coor;

	wall.x -= data->player.pos.x;
	wall.y -= data->player.pos.y;
	steps = (int)fmax(fabs(wall.x), fabs(wall.y));
	if (!steps)
		steps = 1;
	inc.x = wall.x / steps;
	inc.y = wall.y / steps;
	steps *= MAP_EDGE_L;
	coor.x = map.x;
	coor.y = map.y;
	while (steps >= 0 && ft_is_in_map_bound(map, coor.x, coor.y) == 1)
	{
		data->mlx.img.get_addr
		[(int)round(coor.y) * WIDTH + (int)round(coor.x)]
			= ft_create_color(0, 0, 255, 0);
		coor.x += inc.x;
		coor.y += inc.y;
		steps--;
	}
}

void	ft_draw_rays(t_data *data, t_mini_map map)
{
	t_coordinates	wall;
	double			degree;
	double			angle;

	degree = 0;
	while (degree <= FOV)
	{
		angle = ft_update_radian(data->player.angle,
				ft_deg_to_rad(degree - (FOV / 2)));
		wall = ft_wall_hit(data, data->player.pos, angle, NULL);
		while (data->map.map[(int)wall.y][(int)wall.x] == OPENED_DOOR)
			wall = ft_wall_hit(data, wall, angle, NULL);
		ft_draw_mini_map_line(data, wall, map);
		degree += 0.5;
	}
}
