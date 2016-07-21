/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 17:26:47 by scaussin          #+#    #+#             */
/*   Updated: 2016/05/21 20:56:47 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	parser(t_env *e, int cs, t_protocol msg)
{
	int			i;
	char		*str_protocol;

	i = 0;
	str_protocol = protocol_to_string(msg);
	ft_printf("in <= %s", str_protocol);
	free(str_protocol);
	while (i < SIZE_PTR_FUNC)
	{
		if (!ft_strcmp(msg.command, e->ptr_func[i].name))
		{
			e->ptr_func[i].func(e, cs, msg);
			return ;
		}
		i++;
	}
	cmd_unknown(e, cs, msg);
}
