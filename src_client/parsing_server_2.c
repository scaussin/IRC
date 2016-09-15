/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_server_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/02 16:33:24 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/02 16:41:34 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

void	cmd_privmsg_server(t_client *e, t_protocol *msg)
{
	char	*origin;

	e = e + 0;
	if (!msg->params || !msg->params[0] || !msg->params[0][0])
	{
		write_log("warning", "error params PRIVMSG");
		return ;
	}
	if (msg->trailer)
	{
		origin = formate_origin_privmsg(msg);
		ft_printf("[%s] : %s\n", origin, msg->trailer);
		free(origin);
	}
}

char	*formate_origin_privmsg(t_protocol *msg)
{
	char	*origin;
	char	*from_nick;

	from_nick = extract_nick_prefix(msg->prefix);
	origin = Xv(NULL, malloc(ft_strlen(from_nick) + ft_strlen(msg->params[0]) + 3), "malloc");
	if (msg->params[0][0] == '#')
	{
		ft_strcat(origin, msg->params[0]);
		ft_strcat(origin, "->");
		ft_strcat(origin, from_nick);
	}
	else
	{
		ft_strcat(origin, from_nick);
		ft_strcat(origin, "->");
		ft_strcat(origin, msg->params[0]);
	}
	if (from_nick)
		free(from_nick);
	return (origin);
}

void	cmd_part_server(t_client *e, t_protocol *msg)
{
	char	*user;

	if (msg && msg->prefix && msg->params[0] && msg->params
		&& msg->params[0] && msg->params[0][0])
	{
		user = extract_nick_prefix(msg->prefix);
		ft_printf("\033[31m[leave]\033[0m %s leave %s\n", user, msg->params[0]);
		if (e->chan)
			free(e->chan);
		if (user)
			free(user);
		e->chan = NULL;
	}
}

void	cmd_already_registered_server(t_client *e, t_protocol *msg)
{
	msg = msg + 0;
	e = e + 0;
}

void	cmd_nick_server(t_client *e, t_protocol *msg)
{
	msg = msg + 0;
	e->nick[0] = 0;
	write_log("warning", "nickname is already in use");
	ft_printf("Enter your nickname : ");
}
