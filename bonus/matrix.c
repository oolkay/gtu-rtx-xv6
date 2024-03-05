/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 18:40:44 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 15:01:12 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

int	ft_matrix_len(void **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

void	ft_free_matrix(void **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_add_back_matrix_str(char **array, char *str)
{
	char	**new_array;
	size_t	array_len;
	size_t	i;

	array_len = 0;
	if (array)
		array_len = ft_matrix_len((void **)array);
	new_array = (char **)ft_calloc(array_len + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	while (i < array_len)
	{
		new_array[i] = ft_strdup(array[i]);
		if (!new_array[i])
			return (ft_free_matrix((void **)new_array), NULL);
		i++;
	}
	new_array[i] = ft_strdup(str);
	if (!new_array[i])
		return (ft_free_matrix((void **)new_array), NULL);
	ft_free_matrix((void **)array);
	new_array[i + 1] = NULL;
	return (new_array);
}

void	ft_fill_garbage(int arr[], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arr[i] = 0;
		i++;
	}
}
