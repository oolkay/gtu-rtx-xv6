/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 11:29:52 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 11:29:53 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes_bonus/cub3d.h"

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
