/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 18:59:27 by scaussin          #+#    #+#             */
/*   Updated: 2013/11/24 11:37:33 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && ((char *)src)[i] != c)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	if (i == n)
		return (NULL);
	((char *)dest)[i] = ((char *)src)[i];
	return (&((char *)dest)[i + 1]);
}
