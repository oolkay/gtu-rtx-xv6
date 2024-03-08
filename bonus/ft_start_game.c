/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:16:47 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 21:36:22 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_key_press(int k_code, t_data *data)
{
	if (k_code == W)
		data->player.move.y = -1;
	else if (k_code == S)
		data->player.move.y = 1;
	else if (k_code == A)
		data->player.move.x = -1;
	else if (k_code == D)
		data->player.move.x = 1;
	else if (k_code == LEFT)
		data->player.rotate = -1;
	else if (k_code == RIGHT)
		data->player.rotate = 1;
	else if (k_code == ESC)
		ft_free_and_exit(data, EXIT_SUCCESS);
	return (0);
}

static int	ft_key_release(int k_code, t_data *data)
{
	if (k_code == W || k_code == S)
		data->player.move.y = 0;
	else if (k_code == A || k_code == D)
		data->player.move.x = 0;
	else if (k_code == LEFT || k_code == RIGHT)
		data->player.rotate = 0;
	return (0);
}

int	ft_start_game(t_data *data)
{
	data->mlx.win = (void *)mlx_new_window(data->mlx.display_connector,
			WIDTH, HEIGHT, "cub3d-made by cbolat and alcelik");
	mlx_string_put(data->mlx.display_connector, data->mlx.win, 10, 10, 0xFF0000, "WASD to move");
	if (!data->mlx.win)
	{
		printf("Error\nCouldn't open window.\n");
		return (-1);
	}
	data->player.move.x = 0;
	data->player.move.y = 0;
	data->player.rotate = 0;
	// mlx_mouse_hide(data->mlx.display_connector, data->mlx.win);
	mlx_hook(data->mlx.win,  2, 1L<<0, ft_key_press, data);
	mlx_hook(data->mlx.win, 3, 1L<<1, ft_key_release, data);
	mlx_hook(data->mlx.win, ON_EXIT, NO_MASK, ft_free_and_exit, data);
	mlx_loop_hook(data->mlx.display_connector, ft_update, data);
	mlx_loop(data->mlx.display_connector);
	return (1);
}
