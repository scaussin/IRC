/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:42:47 by scaussin          #+#    #+#             */
/*   Updated: 2013/11/27 11:15:02 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	int		i;

	i = ft_strlen(src);
	while (i != -1)
	{
		if (src[i] == (char)c)
			return (&((char *)src)[i]);
		i--;
	}
	return (NULL);
}
