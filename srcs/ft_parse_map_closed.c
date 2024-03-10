/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map_closed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:16:16 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 14:50:42 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_is_component_sur(char **map, int i, int j)
{
	if ((map[i][j + 1] && ft_strchr("0NSEW", map[i][j + 1]))
		|| (j - 1 > 0 && map[i][j - 1] && ft_strchr("0NSEW", map[i][j - 1]))
		|| (map[i + 1] && map[i + 1][j] && ft_strchr("0NSEW", map[i + 1][j]))
		|| (i - 1 > 0 && map[i - 1] && map[i - 1][j]
						&& ft_strchr("0NSEW", map[i - 1][j])))
		return (1);
	return (0);
}

static int	ft_space_surr_check(char **map, int i, int j)
{
	if (!map[i][j + 1] || (map[i][j + 1] && map[i][j + 1] == ' '))
		return (1);
	if (j - 1 < 0 || (j - 1 >= 0 && map[i][j - 1] == ' '))
		return (1);
	if (!map[i + 1] || (map[i + 1] && j >= (int)ft_strlen(map[i + 1]))
		|| (map[i + 1] && j < (int)ft_strlen(map[i + 1])
			&& map[i + 1][j] == ' '))
		return (1);
	if (i - 1 < 0 || (i - 1 >= 0 && j >= (int)ft_strlen(map[i - 1]))
		|| (i - 1 >= 0 && j < (int)ft_strlen(map[i - 1])
			&& map[i - 1][j] == ' '))
		return (1);
	if (i - 1 >= 0 && j - 1 >= 0 && map[i - 1][j - 1] == ' ')
		return (1);
	if (i - 1 >= 0 && j + 1 < (int)ft_strlen(map[i])
		&& map[i - 1][j + 1] == ' ')
		return (1);
	if (i + 1 < ft_matrix_len((void **)map) && j - 1 >= 0
		&& map[i + 1][j - 1] == ' ')
		return (1);
	if (i + 1 < ft_matrix_len((void **)map) && j + 1 < (int)ft_strlen(map[i])
		&& map[i + 1][j + 1] == ' ')
		return (1);
	return (0);
}

static int	ft_surrounding_check(char **map, int i, int j)
{
	if (map[i][j] == ' ' && ft_is_component_sur(map, i, j))
		return (printf("Error\nInvalid map: misplaced space ' ' \n"), 0);
	else if (ft_strchr("0NSEW", map[i][j]))
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
			if (ft_strchr(" 0NWSE", map->map[index[0]][index[1]]))
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
