/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbolat <cbolat@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:03:03 by cbolat            #+#    #+#             */
/*   Updated: 2022/10/16 15:33:56 by cbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*lastspot;

	lastspot = 0;
	if (c > 127)
		return ((char *)s);
	while (*s)
	{
		if (*s == c)
			lastspot = (char *)s;
		s++;
	}
	if (lastspot)
		return (lastspot);
	if (c == '\0')
		return ((char *)s);
	return (0);
}
