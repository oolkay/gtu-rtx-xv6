/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:40:53 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/19 13:27:48 by cbolat           ###   ########.fr       */
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

# define FOV 60
# define ROT_SPEED 0.1
# define COLLECT_FRAME 0.2
# define DOOR_FRAME 1
# define OFF_SET 0.5
# define SPEED 0.25

# define WIDTH 800
# define HEIGHT 800

# define F_C_COLOR_DEF -255

#endif
