/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:46:51 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 21:34:45 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_dimen
{
	double	width;
	double	height;
}	t_dimen;

typedef struct s_coordinates
{
	double	x;
	double	y;
}	t_coordinates;

typedef struct s_object
{
	double	x;
	double	y;
	double	frame;
}	t_object;

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

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

typedef struct s_mlx
{
	void	*display_connector;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct s_render
{
	double			degree;
	double			angle;
	t_coordinates	wall_hit;
	t_dimen			wall_dimen;
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
	double					angle;
	double					rotate;
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
}	t_map;

typedef struct s_data
{
	t_mlx			mlx;
	t_player		player;
	t_map			map;
}	t_data;

#endif
