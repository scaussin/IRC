/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protocol_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 09:52:20 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/21 09:52:44 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

char	**malloc_params(int size)
{
	char	**params;
	int		i;

	i = 0;
	params = (char **)Xv(NULL, malloc(sizeof(char *) * (size + 1)), "malloc");
	params[size] = NULL;
	while (i < size)
	{
		params[i] = (char *)Xv(NULL, malloc(sizeof(char) * MAX_SIZE_MSG_IRC)
			, "malloc");
		ft_bzero(params[i], MAX_SIZE_MSG_IRC);
		i++;
	}
	return (params);
}