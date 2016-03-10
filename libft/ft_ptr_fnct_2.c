/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_fnct_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:57:44 by scaussin          #+#    #+#             */
/*   Updated: 2015/04/03 15:51:32 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_printf_x_va(va_list ap)
{
	return (ft_printf_x(va_arg(ap, unsigned int)));
}

static int	ft_printf_xx_va(va_list ap)
{
	return (ft_printf_xx(va_arg(ap, unsigned int)));
}

static int	ft_printf_d_va(va_list ap)
{
	return (ft_printf_d(va_arg(ap, int)));
}

static int	ft_printf_per100_va(va_list ap)
{
	ap = ap + 0;
	return (ft_printf_c('%'));
}

void		ft_init_fun_tab(t_fct tab[SIZE_TAB_FNCT])
{
	tab[0].c = 'd';
	tab[0].fnct = ft_printf_d_va;
	tab[1].c = 'i';
	tab[1].fnct = ft_printf_d_va;
	tab[2].c = 'u';
	tab[2].fnct = ft_printf_u_va;
	tab[3].c = 'o';
	tab[3].fnct = ft_printf_o_va;
	tab[4].c = 's';
	tab[4].fnct = ft_printf_s_va;
	tab[5].c = 'c';
	tab[5].fnct = ft_printf_c_va;
	tab[6].c = 'x';
	tab[6].fnct = ft_printf_x_va;
	tab[7].c = 'p';
	tab[7].fnct = ft_printf_p_va;
	tab[8].c = 'X';
	tab[8].fnct = ft_printf_xx_va;
	tab[9].c = '%';
	tab[9].fnct = ft_printf_per100_va;
}
