/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:46:51 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/10 16:39:54 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_img
{
	void	*img;
	int		height;
	int		width;
	int		bits_per_pixel;
	int		line_length;
	int		steps;
	int		*get_addr;
}	t_img;

typedef struct s_coordinates
{
	double	x;
	double	y;
}	t_coordinates;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_mlx
{
	void		*display_connector;
	void		*win;
	t_img		img;
}	t_mlx;

typedef struct s_render
{
	double			degree;
	double			angle;
	t_coordinates	wall_hit;
	double			distance;
	int				direction;
	double			wall_height;
	int				y_tex;
}	t_render;

typedef struct s_player
{
	t_coordinates			pos;
	t_coordinates			dir;
	t_coordinates			move;
	int 					door_signal;
	double					angle;
	double					rotate;
	double					angle_rad;
}	t_player;

typedef struct s_map
{
	t_img			north;
	t_img			south;
	t_img			west;
	t_img			east;
	char			**map;
	int				ceiling_c;
	int				floor_c;
	int				show_minimap;
}	t_map;

typedef struct s_data
{
	t_mlx			mlx;
	t_player		player;
	t_map			map;
	t_img			minimap;
	t_img			door;
	t_img 			door_open;
}	t_data;

#endif
