/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acepni <acepni@student.42.tr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:46:51 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/09 17:07:15 by acepni           ###   ########.fr       */
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

typedef struct s_mini_map
{
	double	x;
	double	y;
	double	radius;
	t_img	img;
}	t_mini_map;

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

typedef struct s_i_spr
{
	int		frames;
	t_img	*img;
}	t_i_spr;

typedef struct s_mlx
{
	void	*display_connector;
	void	*win;
	t_img	img;
	t_mini_map	mini_map;
}	t_mlx;

typedef struct s_sprite
{
	t_coordinates	screen;
	t_coordinates	collecs;
	t_coordinates	textures;
	t_dimen			sprite;
}	t_sprite;

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
	t_i_spr			door;
	t_i_spr			collec;
	t_list			*ll_door;
	t_list			*ll_collect;
	char			**map;
	int				ceiling_c;
	int				floor_c;
	double			depth[WIDTH];
	t_coordinates	sprite;

}	t_map;

typedef struct s_data
{
	t_mlx			mlx;
	t_player		player;
	t_map			map;
    t_img           minimap;
}	t_data;


#endif
