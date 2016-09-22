/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 15:28:59 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/22 19:33:24 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*cpy;

	i = 0;
	if (s1)
	{
		cpy = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
		while (s1[i])
		{
			cpy[i] = s1[i];
			i++;
		}
		cpy[i] = 0;
		return (cpy);
	}
	return (NULL);
}
