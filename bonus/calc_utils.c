/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:29:48 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 12:41:22 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

double	ft_distance(t_coordinates p1, t_coordinates p2)
{
	t_coordinates	distance;

	distance.x = powf(p2.x - p1.x, 2);
	distance.y = powf(p2.y - p1.y, 2);
	return (sqrtf(distance.x + distance.y));
}

int	ft_create_color(int transpancy, int r, int g, int b)
{
	return (transpancy << 24 | r << 16 | g << 8 | b);
}

double	ft_update_radian(double radian, double inc)
{
	radian += inc;
	if (radian > 2 * PI)
		radian -= 2 * PI;
	else if (radian < 0)
		radian += 2 * PI;
	return (radian);
}

double	ft_deg_to_rad(double degree)
{
	return ((degree * PI) / 180.0);
}

static int	is_map(const t_data *data, float x, float y)
{
	if (y < 0 || y > ft_matrix_len((void **)data->map.map))
		return (0);
	if (x < 0 || x > ft_strlen(data->map.map[(int)y]))
		return (0);
	return (1);
}
