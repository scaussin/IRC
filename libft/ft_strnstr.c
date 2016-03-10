/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 14:24:50 by scaussin          #+#    #+#             */
/*   Updated: 2013/12/02 10:35:29 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *test, size_t n)
{
	unsigned int	i;
	int				j;

	i = 0;
	if (test[i] == 0)
		return ((char *)src);
	while (src[i] && i < n)
	{
		j = 0;
		while (src[i + j] == test[j] && (i + j) < n)
		{
			if (test[j + 1] == '\0')
				return (&((char *)src)[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
