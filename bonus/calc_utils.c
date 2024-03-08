/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oolkay <oolkay@42.tr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 01:01:27 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/07 18:45:34 by oolkay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



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
