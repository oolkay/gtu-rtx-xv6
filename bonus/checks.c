/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:29:52 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 14:10:58 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

void ft_open_door(t_data *data, t_render *r)
{
	if(data->map.map[(int)(r->wall_hit.y)][(int)(r->wall_hit.x)] == '2'
		&& r->distance < 1)
	{
		if (data->map.map[(int)(r->wall_hit.y)][(int)(r->wall_hit.x)] == '2')
			data->map.map[(int)(r->wall_hit.y)][(int)(r->wall_hit.x)] = '3';
	}
	else if (data->map.map[(int)(r->wall_hit.y)][(int)(r->wall_hit.x)] == '3'
		&& r->distance < 1)
	{
		if (data->map.map[(int)(r->wall_hit.y)][(int)(r->wall_hit.x)] == '3')
			data->map.map[(int)(r->wall_hit.y)][(int)(r->wall_hit.x)] = '2';
	}
	data->player.door_signal = 0;
}

int	ft_extention_check(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 4)
		return (0);
	if (ft_strcmp(str + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
