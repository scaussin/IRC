/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 17:18:00 by scaussin          #+#    #+#             */
/*   Updated: 2015/05/09 22:23:56 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	int		len1;

	if (s1 || s2)
	{
		len1 = ft_strlen(s1);
		if (!(s = (char *)malloc((sizeof(char) * (len1 + ft_strlen(s2))) + 1)))
			return (NULL);
		ft_strcpy(s, s1);
		ft_strcpy(&(s[len1]), s2);
		return (s);
	}
	return (NULL);
}
