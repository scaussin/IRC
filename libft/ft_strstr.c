/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:52:14 by scaussin          #+#    #+#             */
/*   Updated: 2013/11/30 12:40:22 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *src, const char *test)
{
	int		i;
	int		j;

	i = 0;
	if (test[i] == 0)
		return ((char *)src);
	while (src[i])
	{
		j = 0;
		while (src[i + j] == test[j])
		{
			if (test[j + 1] == '\0')
				return (&((char *)src)[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
