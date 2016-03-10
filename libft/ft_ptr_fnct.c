/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_fnct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:57:00 by scaussin          #+#    #+#             */
/*   Updated: 2013/12/27 19:57:01 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_printf_u_va(va_list ap)
{
	return (ft_printf_u(va_arg(ap, unsigned int)));
}

int		ft_printf_o_va(va_list ap)
{
	return (ft_printf_o(va_arg(ap, unsigned int)));
}

int		ft_printf_s_va(va_list ap)
{
	return (ft_printf_s(va_arg(ap, char *)));
}

int		ft_printf_c_va(va_list ap)
{
	return (ft_printf_c(va_arg(ap, int)));
}

int		ft_printf_p_va(va_list ap)
{
	return (ft_printf_p(va_arg(ap, unsigned long)));
}
