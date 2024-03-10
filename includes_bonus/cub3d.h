/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:46:57 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/10 11:57:45 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "libs.h"

int ft_matrix_len(void **arr);
void ft_free_matrix(void **arr);
int ft_import_map(t_data *data, char *argv);
int ft_extention_check(char *str);
int ft_fill_textures(t_data *data, int fd);
int ft_is_number(char *str);
int ft_parse_map(t_map *map, int fd);
char **ft_add_back_matrix_str(char **array, char *str);
t_list *ll_new(void *data);
void ll_add_head(t_list **list, t_list *new);
int ft_init_images(t_data *data);
int ft_start_game(t_data *data);
int ft_update(t_data *data);
double ft_update_radian(double radian, double inc);
void ft_ll_clear(t_list **list);
double ft_deg_to_rad(double degree);
double ft_distance(t_coordinates p1, t_coordinates p2);
int ft_create_color(int transpancy, int r, int g, int b);
int ft_free_and_exit(t_data *data, int status);
void ft_fill_garbage(int arr[], int size);
int ft_assign_texture(t_data *data, char **sp);
int ft_check_map_closed(t_map *map);
void ft_move_player(t_data *data);
void ft_render(t_data *data);
void ft_draw_wall(t_data *data, t_render *r, int i);
void ft_draw_minimap(t_data *data, int x, int y, t_coordinates pos);
t_coordinates ft_wall_hit(t_data *data, t_coordinates pos,
						  double angle, int *dir);
void ft_draw_rays(t_data *data, t_render *r, int i);
void ft_draw_banner(t_data *data);

#endif
