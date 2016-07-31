/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 11:09:34 by scaussin          #+#    #+#             */
/*   Updated: 2016/07/30 22:10:16 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	int		i;

	i = 0;
	while (src && src[i])
	{
		if (src[i] == (char)c)
			return (&((char *)src)[i]);
		i++;
	}
	if ((char)c == '\0' && src)
		return (&((char *)src)[i]);
	return (NULL);
}
