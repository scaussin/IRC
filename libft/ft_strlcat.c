/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 09:55:30 by scaussin          #+#    #+#             */
/*   Updated: 2013/11/25 11:16:04 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len;
	size_t	len2;
	size_t	result;

	len = ft_strlen(dest);
	len2 = ft_strlen(src);
	result = size - len - 1;
	if (size > len)
		ft_strncat(dest, src, result);
	else
		return (len2 + size);
	return (len + len2);
}
