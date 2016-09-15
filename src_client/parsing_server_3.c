/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_server_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 16:34:58 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/02 16:42:04 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

char	*extract_nick_prefix(char *prefix)
{
	char	*nick = NULL;

	nick = ft_strdup(prefix + 1);
	if (ft_strchr(nick, '!'))
	{
		*(ft_strchr(nick, '!')) = 0;
		return (nick);
	}
	return (NULL);
}

void	cmd_names_server(t_client *e, t_protocol *msg)
{
	e = e + 0;

	ft_printf("\033[94m[who]\033[0m %s\n", msg->trailer);
}

void	cmd_end_names_server(t_client *e, t_protocol *msg)
{
	e = e + 0;
	msg = msg + 0;
}

void	cmd_list_server(t_client *e, t_protocol *msg)
{
	e = e + 0;

	if (msg && msg->params && msg->params[0] && msg->params[0][0])
		ft_printf("\033[36m[list]\033[0m %s\n", msg->params[0]);
}

void	cmd_start_end_list_server(t_client *e, t_protocol *msg)
{
	e = e + 0;
	msg = msg + 0;
}
