/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:59:47 by scaussin          #+#    #+#             */
/*   Updated: 2013/12/27 19:59:48 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_p(unsigned long nbr)
{
	int				ret;
	unsigned long	copy;

	copy = nbr;
	ret = 0;
	if (nbr == 0)
		ret++;
	while (nbr >= 1)
	{
		nbr = nbr / 16;
		ret++;
	}
	ft_putstr("0x");
	ft_putnbr_p(copy);
	return (ret + 2);
}

int		ft_printf_xx(unsigned int nbr)
{
	int		ret;
	int		copy;

	copy = nbr;
	ret = 0;
	if (nbr == 0)
		ret++;
	while (nbr >= 1)
	{
		nbr = nbr / 16;
		ret++;
	}
	ft_putnbr_xx(copy);
	return (ret);
}

int		ft_printf_x(unsigned int nbr)
{
	int		ret;
	int		copy;

	copy = nbr;
	ret = 0;
	if (nbr == 0)
		ret++;
	while (nbr >= 1)
	{
		nbr = nbr / 16;
		ret++;
	}
	ft_putnbr_x(copy);
	return (ret);
}
