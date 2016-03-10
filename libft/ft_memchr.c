/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 11:23:55 by scaussin          #+#    #+#             */
/*   Updated: 2013/12/27 20:28:25 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	if (src == NULL)
		return (NULL);
	while (i < n)
	{
		if (((unsigned char *)src)[i] == (unsigned char)c)
			return (&((unsigned char *)src)[i]);
		i++;
	}
	return (NULL);
}
