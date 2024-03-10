/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:40:53 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/10 17:42:52 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "./defines/keys.h"
# include "./defines/map.h"

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_EXIT 17
# define NO_MASK 0

# define FOV 60
# define ROT_SPEED 0.025
# define OFF_SET 0.5
# define SPEED 0.025

# define WIDTH 1000
# define HEIGHT 1000

# define PI 3.14159265358979323846

# define ANGLE_RAD ((float)(FOV * PI / 180) / (float)(WIDTH))

# define F_C_COLOR_DEF -255

#endif
