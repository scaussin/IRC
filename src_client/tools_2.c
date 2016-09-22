/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 09:46:03 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/21 13:56:51 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

int		str_equal(char *s1, char *s2)
{
	int		i;

	i = 0;
	if(s1 && s2)
	{
		while (s1[i] == s2[i])
		{
			if (s1[i] == 0)
				return (1);
			i++;
		}
		return (0);
	}
	else
	{
		if (s1 == s2)
			return (1);
	}
	return (0);
}

void	free_tab_2d(char **params)
{
	int		i;

	i = 0;
	if (params)
	{
		while (params[i])
		{
			free(params[i]);
			i++;
		}
		free(params);
	}
}