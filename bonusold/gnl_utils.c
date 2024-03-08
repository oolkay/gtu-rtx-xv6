/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:33:59 by cbolat            #+#    #+#             */
/*   Updated: 2023/08/20 15:01:12 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/cub3d.h"

char	*ft_strsjoin(char *d_line, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!d_line)
	{
		d_line = (char *)malloc(1 * sizeof(char));
		d_line[0] = '\0';
	}
	if (!d_line || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(d_line) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (d_line)
		while (d_line[++i] != '\0')
			str[i] = d_line[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(d_line) + ft_strlen(buff)] = '\0';
	free(d_line);
	return (str);
}

char	*ft_get_line(char *d_line)
{
	int		i;
	char	*str;

	i = 0;
	if (!d_line[i])
		return (NULL);
	while (d_line[i] && d_line[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (d_line[i] && d_line[i] != '\n')
	{
		str[i] = d_line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_new_dinamic_line(char *d_line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (d_line[i] && d_line[i] != '\n')
		i++;
	if (!d_line[i])
	{
		free(d_line);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(d_line) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (d_line[i])
		str[j++] = d_line[i++];
	str[j] = '\0';
	free(d_line);
	return (str);
}
