/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map_closed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 13:38:51 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 15:01:12 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

static int	ft_is_component_sur(char **map, int i, int j)
{
	if ((map[i][j + 1] && ft_strchr("0NSEWC", map[i][j + 1]))
		|| (j - 1 > 0 && map[i][j - 1] && ft_strchr("0NSEWC", map[i][j - 1]))
		|| (map[i + 1] && map[i + 1][j] && ft_strchr("0NSEWC", map[i + 1][j]))
		|| (i - 1 > 0 && map[i - 1] && map[i - 1][j]
			&& ft_strchr("0NSEWC", map[i - 1][j])))
		return (1);
	return (0);
}

static int	ft_space_surr_check(char **map, int i, int j)
{
	if (!map[i][j + 1]
		|| (map[i][j + 1]
			&& map[i][j + 1] == ' '))
		return (1);
	else if (j - 1 < 0
		|| (j - 1 >= 0
			&& map[i][j - 1] == ' '))
		return (1);
	else if (!map[i + 1]
		|| (map[i + 1]
			&& j >= (int)ft_strlen(map[i + 1]))
		|| (map[i + 1]
			&& j < (int)ft_strlen(map[i + 1])
			&& map[i + 1][j] == ' '))
		return (1);
	else if (i - 1 < 0
		|| (i - 1 >= 0
			&& j >= (int)ft_strlen(map[i - 1]))
		|| (i - 1 >= 0
			&& j < (int)ft_strlen(map[i - 1])
			&& map[i - 1][j] == ' '))
		return (1);
	return (0);
}

static int	ft_check_wall_placement(char **map, int i, int j)
{
	if (map[i][j + 1] && map[i][j + 1] == WALL
		&& j - 1 > 0 && map[i][j - 1] && map[i][j - 1] == WALL
		&& map[i + 1] && map[i + 1][j] && map[i + 1][j] != ' '
		&& i - 1 > 0 && map[i - 1] && map[i - 1][j] && map[i - 1][j] != ' ')
		return (1);
	else if (map[i + 1] && map[i + 1][j] && map[i + 1][j] == WALL
		&& i - 1 > 0 && map[i - 1] && map[i - 1][j] && map[i - 1][j] == WALL
		&& map[i][j + 1] && map[i][j + 1] != ' '
		&& j - 1 > 0 && map[i][j - 1] && map[i][j - 1] != ' ')
		return (1);
	return (0);
}

static int	ft_surrounding_check(char **map, int i, int j)
{
	if (map[i][j] == ' ' && ft_is_component_sur(map, i, j))
		return (printf("Error\nInvalid map: misplaced space ' ' \n"), 0);
	else if (ft_strchr("0NSEWC", map[i][j]))
	{
		if (ft_space_surr_check(map, i, j) == 1)
		{
			if (map[i][j] == EMPTY_SPACE)
				printf("Error\nInvalid map: misplaced space '0'\n");
			else
				printf("Error\nInvalid map: misplaced component\n");
			return (0);
		}
	}
	else if ((map[i][j] == CLOSED_DOOR || map[i][j] == OPENED_DOOR)
		&& ft_check_wall_placement(map, i, j) == 0)
		return (printf("Error\nInvalid map: misplaaced wall\n"), 0);
	return (1);
}

int	ft_check_map_closed(t_map *map)
{
	int	index[2];

	ft_fill_garbage(index, 2);
	while (map->map[index[0]])
	{
		index[1] = 0;
		while (map->map[index[0]][index[1]])
		{
			if (ft_strchr(" 023NWSEC", map->map[index[0]][index[1]]))
			{
				if (ft_surrounding_check(map->map, index[0], index[1]) == 0)
					return (0);
			}
			index[1]++;
		}
		index[0]++;
	}
	return (1);
}
