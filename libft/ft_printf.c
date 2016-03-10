/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/27 19:56:30 by scaussin          #+#    #+#             */
/*   Updated: 2015/04/02 18:48:29 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_match_fnct(char c, va_list ap)
{
	t_fct	tab_fnct[SIZE_TAB_FNCT];
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	ft_init_fun_tab(tab_fnct);
	while (i < SIZE_TAB_FNCT && tab_fnct[i].c != c)
		i++;
	if (i < SIZE_TAB_FNCT)
		ret = tab_fnct[i].fnct(ap);
	else
	{
		ft_putchar(c);
		ret++;
	}
	return (ret);
}

static int		ft_manage(char *str, va_list ap)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			ret = ft_match_fnct(str[i + 1], ap) + ret;
			i = i + 2;
		}
		if (str[i] != '\0' && str[i] != '%')
		{
			ft_putchar(str[i]);
			ret++;
			i++;
		}
	}
	return (ret);
}

int				ft_printf(const char *str, ...)
{
	va_list		ap;
	int			ret;

	ret = 0;
	va_start(ap, str);
	ret = ft_manage((char *)str, ap);
	va_end(ap);
	return (ret);
}
