/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:47:24 by cbolat            #+#    #+#             */
/*   Updated: 2022/10/16 17:47:26 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l_i;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		l_i = 0;
		if (big[i] == little[l_i])
		{
			while (i + l_i < len && big[i + l_i] == little[l_i])
			{
				l_i++;
				if (little[l_i] == '\0')
					return ((char *)(big + i));
			}
		}
		i++;
	}
	return (0);
}
