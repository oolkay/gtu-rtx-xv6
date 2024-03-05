/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:46:57 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/19 19:55:50 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs.h"

int				ft_matrix_len(void **arr);
void			ft_free_matrix(void **arr);
int				ft_import_map(t_data *data, char *argv);
int				ft_extention_check(char *str);
int				ft_fill_textures(t_data *data, int fd);
int				ft_is_number(char *str);
int				ft_parse_map(t_map *map, int fd);
char			**ft_add_back_matrix_str(char **array, char *str);
t_object		*ft_create_obj(int frame, int x, int y);
t_list			*ll_new(void *data);
void			ll_add_head(t_list **list, t_list *new);
int				ft_init_images(t_data *data);
int				ft_start_game(t_data *data);
int				ft_update(t_data *data);
double			ft_update_radian(double radian, double inc);
void			ft_ll_remove(t_list **list, int x, int y);
void			ft_ll_clear(t_list **list);
double			ft_deg_to_rad(double degree);
double			ft_distance(t_coordinates p1, t_coordinates p2);
int				ft_ll_find(t_list *head, int x, int y);
int				ft_create_color(int transpancy, int r, int g, int b);
int				ft_free_and_exit(t_data *data, int status);
void			ft_fill_garbage(int arr[], int size);
int				ft_assign_texture(t_data *data, char **sp);
int				ft_check_map_closed(t_map *map);
void			ft_move_player(t_data *data);
void			ft_door_sprite(t_data *data);
void			ft_wall_dimension(t_data *data,
					t_render *render, t_coordinates pos, double degree);
void			ft_render(t_data *data, double degree);
void			ft_draw_wall(t_data *data, t_list *ll_render);
void			ft_render_mini_map(t_data *data);
t_coordinates	ft_wall_hit(t_data *data, t_coordinates pos,
					double angle, int *dir);
int				ft_max(double x, double y);
void			ft_draw_rays(t_data *data, t_mini_map map);
void			ft_draw_comps(t_data *data, t_mini_map map);
int				ft_is_in_map_bound(t_mini_map map, double x, double y);
void			ft_open_close_door(t_data *data);
void			ft_sprites(t_data *data);
void			ft_draw_circle(int	*data, t_mini_map map, int color);

#endif
