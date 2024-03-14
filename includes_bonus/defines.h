/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 17:40:53 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/10 18:47:48 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "./defines/keys.h"
# include "./defines/map.h"
# include "./defines/mini_map.h"

# define ON_KEYDOWN 2
# define ON_KEYUP 3
# define ON_MOUSEMOVE 6
# define ON_EXIT 17
# define NO_MASK 0

# define FOV 60
# define OFF_SET 0.5
# define SPEED 0.025

# define WIDTH 800
# define HEIGHT 800
# define MWIDTH 20
# define MHEIGHT 20
# define ROT_SPEED 0.05

# define PI 3.14159265358979323846

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define ORANGE 0xFFA500
# define PURPLE 0x800080
# define PINK 0xFFC0CB
# define BROWN 0xA52A2A
# define GREY 0x808080
# define LIGHT_GREY 0xD3D3D3
# define DARK_GREY 0xA9A9A9
# define LIGHT_BLUE 0xADD8E6
# define LIGHT_GREEN 0x90EE90
# define TRANSPARENT 0xFF000000
# define F_C_COLOR_DEF -255

#endif
