/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 15:19:23 by scaussin          #+#    #+#             */
/*   Updated: 2015/04/29 09:08:10 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		n;
	int		k;

	i = 0;
	n = 0;
	k = 0;
	if ((str[i] < 48 || str[i] > 57) && (str[i] < 9 || str[i] > 13)
		&& str[i] != ' ' && str[i] != '+' && str[i] != '-')
		return (n);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k++;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		n = (str[i] - 48) + n * 10;
		i++;
	}
	return (n = (k != 0) ? n * (-1) : n);
}
