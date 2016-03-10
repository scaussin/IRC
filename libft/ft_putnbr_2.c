/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:59:11 by scaussin          #+#    #+#             */
/*   Updated: 2013/12/27 19:59:12 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_x(unsigned int n)
{
	if (n > 15)
		ft_putnbr_x(n / 16);
	if ((n % 16) + 48 > '9')
		ft_putchar((n % 16) + 87);
	else
		ft_putchar((n % 16) + 48);
}

void	ft_putnbr_xx(unsigned int n)
{
	if (n > 15)
		ft_putnbr_xx(n / 16);
	if ((n % 16) + 48 > '9')
		ft_putchar((n % 16) + 55);
	else
		ft_putchar((n % 16) + 48);
}

void	ft_putnbr_p(unsigned long n)
{
	if (n > 15)
		ft_putnbr_p(n / 16);
	if ((n % 16) + 48 > '9')
		ft_putchar((n % 16) + 87);
	else
		ft_putchar((n % 16) + 48);
}
