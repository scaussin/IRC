/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_server_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 09:59:51 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/21 10:00:15 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

int		extract_params(char ***params, char **msg)
{
	if (!msg || !*msg || !**msg)
		return (0);
	(*params) = ft_strsplit(*msg, ' ');
	return (1);
}

int		extract_trailer(char **trailer, char **msg)
{
	char	*tmp;

	if (!msg || !*msg || !**msg)
		return (0);
	if (*msg[0] == ':')
	{
		*trailer = ft_strdup(*msg + 1);
		**msg = 0;
		return (1);
	}
	if (((tmp) = ft_strstr(*msg, " :")))
	{
		*trailer = ft_strdup(tmp + 2);
		*tmp = 0;
		return (1);
	}
	return (0);
}
