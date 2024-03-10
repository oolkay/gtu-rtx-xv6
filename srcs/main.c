/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omer/baha <oolkay/acepni@gtu.xv6>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:48:24 by omer/baha         #+#    #+#             */
/*   Updated: 2024/03/10 13:17:51 by omer/baha        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	ft_arg_number_check(int argc)
{
	if (argc < 2)
	{
		printf("Error\nMissing map file.\nUSAGE: ./cub3d <file.cub>\n");
		return (0);
	}
	else if (argc > 2)
	{
		printf("Error\nInvalid arguments.\n./cub3d <file.cub>\n");
		return (0);
	}
	return (1);
}

static void	ft_init_mlx(t_data *data)
{
	data->mlx.win = NULL;
	data->mlx.img.img = NULL;
	data->mlx.display_connector = mlx_init();
	if (!data->mlx.display_connector)
	{
		printf("Error\nCouldn't initialize mlx.\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		return_val;

	if (ft_arg_number_check(argc) == 0)
		return (EXIT_FAILURE);
	ft_init_mlx(&data);
	return_val = ft_import_map(&data, argv[1]);
	if (return_val != 1)
		ft_free_and_exit(&data, EXIT_FAILURE);
	return_val = ft_init_images(&data);
	if (return_val != 1)
		ft_free_and_exit(&data, EXIT_FAILURE);
	return_val = ft_start_game(&data);
	if (return_val != 1)
		ft_free_and_exit(&data, EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
