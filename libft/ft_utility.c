/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:59:57 by scaussin          #+#    #+#             */
/*   Updated: 2013/12/27 19:59:59 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_s(char *str)
{
	if (str == NULL)
		return (ft_putstr("(null)"));
	ft_putstr(str);
	return (ft_strlen(str));
}

int		ft_printf_u(unsigned int nbr)
{
	int				ret;
	unsigned int	copy;

	copy = nbr;
	ret = 0;
	if (nbr == 0)
		ret++;
	while (nbr >= 1)
	{
		nbr = nbr / 10;
		ret++;
	}
	ft_putnbr_unsigned(copy);
	return (ret);
}

int		ft_printf_o(unsigned int nbr)
{
	int		ret;
	int		copy;

	copy = nbr;
	ret = 0;
	if (nbr <= 0)
	{
		ft_putstr("0");
		return (1);
	}
	while (nbr >= 1)
	{
		nbr = nbr / 8;
		ret++;
	}
	ft_putnbr_o(copy);
	return (ret);
}

int		ft_printf_d(int nbr)
{
	int		ret;
	int		copy;

	copy = nbr;
	ret = 0;
	if (nbr <= 0)
		ret++;
	while (nbr >= 1 || nbr <= -1)
	{
		nbr = nbr / 10;
		ret++;
	}
	ft_putnbr(copy);
	return (ret);
}

int		ft_printf_c(char c)
{
	ft_putchar(c);
	return (1);
}
