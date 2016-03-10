/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 13:29:22 by scaussin          #+#    #+#             */
/*   Updated: 2014/01/24 15:31:09 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (s)
	{
		new = (char *)malloc((sizeof(char) * len) + 1);
		if (new == NULL)
			return (NULL);
		while (i < len)
		{
			new[i] = s[start];
			i++;
			start++;
		}
		new[len] = '\0';
		return (new);
	}
	return (NULL);
}
