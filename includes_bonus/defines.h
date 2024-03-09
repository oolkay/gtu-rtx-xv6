/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acepni <acepni@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:40:53 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/09 15:48:32 by acepni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "./defines/keys.h"
# include "./defines/map.h"
# include "./defines/mini_map.h"

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_EXIT 17
# define ON_MOUSEMOVE 6
# define NO_MASK 0

# define COLLECT_FRAME 0.2
# define DOOR_FRAME 1
# define FOV 60
# define OFF_SET 0.5
# define SPEED 0.025

# define WIDTH 800
# define HEIGHT 800

# define ANGLE_RAD ((float)((float)FOV * (float)PI / 180.0f) / (float)(WIDTH))
# define ROT_SPEED 0.05

# define PI 3.14159265358979323846

# define F_C_COLOR_DEF -255

#endif
