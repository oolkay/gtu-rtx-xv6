/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:46:57 by cbolat            #+#    #+#             */
/*   Updated: 2024/03/10 14:59:18 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs.h"

int		ft_matrix_len(void **arr);
void	ft_free_matrix(void **arr);
int		ft_import_map(t_data *data, char *argv);
int		ft_extention_check(char *str);
int		ft_fill_textures(t_data *data, int fd);
int		ft_is_number(char *str);
int		ft_parse_map(t_map *map, int fd);
char	**ft_add_back_matrix_str(char **array, char *str);
int		ft_init_images(t_data *data);
int		ft_start_game(t_data *data);
int		ft_update(t_data *data);
double	ft_update_radian(double radian, double inc);
double	ft_deg_to_rad(double degree);
double	ft_distance(t_coordinates p1, t_coordinates p2);
int		ft_create_color(int transpancy, int r, int g, int b);
int		ft_free_and_exit(t_data *data, int status);
void	ft_fill_garbage(int arr[], int size);
int		ft_assign_texture(t_data *data, char **sp);
int		ft_check_map_closed(t_map *map);
void	ft_move_player(t_data *data);
void	ft_render(t_data *data);
void	ft_draw_wall(t_data *data, t_render *r, int i);
void	ft_draw_minimap(t_data *data, int x, int y, t_coordinates pos);
void	ft_draw_rays(t_data *data, t_render *r);
void	ft_draw_banner(t_data *data);
int		is_map(const t_data *data, float x, float y);
void    ft_open_door(t_data *data, t_render *r);

#endif
