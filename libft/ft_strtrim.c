/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 17:56:47 by scaussin          #+#    #+#             */
/*   Updated: 2013/12/02 10:38:15 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_my_start(char const *s)
{
	int		i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

static int	ft_my_end(char const *s)
{
	int		i;

	i = ft_strlen(s);
	while ((s[i - 1] == ' ' || s[i - 1] == '\n' || s[i - 1] == '\t') && i > 0)
		i--;
	return (i);
}

char		*ft_strtrim(char const *s)
{
	int		start;
	int		end;
	int		i;
	char	*new;

	start = 0;
	end = 0;
	i = 0;
	if (s)
	{
		start = ft_my_start(s);
		end = ft_my_end(s);
		start = (start > end) ? 0 : start;
		new = (char *)malloc((sizeof(char) * (end - start)) + 1);
		if (new == NULL)
			return (NULL);
		while (i < (end - start))
		{
			new[i] = s[start + i];
			i++;
		}
		new[i] = '\0';
		return (new);
	}
	return (NULL);
}
