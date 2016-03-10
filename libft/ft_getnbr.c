/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/19 13:58:27 by scaussin          #+#    #+#             */
/*   Updated: 2013/12/19 16:03:03 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_getnbr(const char *str)
{
	int		i;
	int		n;
	int		k;

	i = 0;
	n = 0;
	k = 0;
	if ((str[i] < '0' || str[i] > '9') && (str[i] < 9 || str[i] > 13)
		&& str[i] != ' ' && str[i] != '+' && str[i] != '-')
		return (n);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' && str[i])
			k++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (str[i] - 48) + n * 10;
		i++;
	}
	return (n = (k % 2 != 0) ? n * (-1) : n);
}
