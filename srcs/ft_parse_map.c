/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 20:26:23 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 15:08:52 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_scan_map(t_map *map, int fd)
{
	char	*line;
	int		empty_line;

	map->map = (char **)ft_calloc(1, sizeof(char *));
	if (!map->map)
		return (printf("Error\nMalloc failed!\n"), 0);
	empty_line = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (*line)
		{
			if (ft_matrix_len((void **)map->map) && empty_line)
				return (printf("Error\nInvalid map.\n"), free(line), 0);
			map->map = ft_add_back_matrix_str(map->map, line);
			if (map->map == NULL)
				return (free(line), 0);
		}
		else if (ft_matrix_len((void **)map->map))
			empty_line = 1;
		free(line);
	}
	return (1);
}

static int	ft_check_map_elem(char c, int *content)
{
	if (ft_strchr(" 01NSEW", c) == 0)
		return (printf("Error\nInvalid map: Invalid component\n"), 0);
	else if (c == PLAYER_N
		|| c == PLAYER_E
		|| c == PLAYER_S
		|| c == PLAYER_W)
		(*content)++;
	return (1);
}

static int	ft_check_map(t_map *map)
{
	int	content;
	int	i[2];

	content = 0;
	ft_fill_garbage(i, 2);
	while (map->map[i[0]])
	{
		i[1] = 0;
		while (map->map[i[0]][i[1]])
		{
			if (ft_check_map_elem(map->map[i[0]][i[1]], &content) == 0)
				return (0);
			i[1]++;
		}
		i[0]++;
	}
	if (content > 1)
		return (printf("Error\nInvalid map: Too many players\n"), 0);
	else if (content < 1)
		return (printf("Error\nInvalid map: Missing player\n"), 0);
	return (1);
}

int	ft_parse_map(t_map *map, int fd)
{
	int	return_value;

	return_value = ft_scan_map(map, fd);
	if (return_value == 0)
		return (0);
	else if (ft_matrix_len((void **)map->map) == 0)
		return (printf("Error\nInvalid map.\n"), 0);
	return_value = ft_check_map(map);
	if (return_value == 0)
		return (0);
	return_value = ft_check_map_closed(map);
	if (return_value == 0)
		return (0);
	return (1);
}
