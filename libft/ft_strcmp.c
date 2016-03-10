/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 14:49:01 by scaussin          #+#    #+#             */
/*   Updated: 2014/01/26 16:38:44 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *src, const char *test)
{
	int		i;

	i = 0;
	while (src[i] == test[i])
	{
		if (src[i] == '\0')
			return (0);
		i++;
	}
	return (((unsigned char)src[i] - (unsigned char)test[i]));
}
