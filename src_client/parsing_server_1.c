/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_server_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 18:24:51 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/21 13:49:21 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

void	parsing_server(t_client *e, t_protocol *msg)
{
	int		i;

	i = 0;
	while (i < NB_PTR_FUNC_SERVER)
	{
		if (!ft_strcmp(msg->command, e->func_server[i].name))
		{
			e->func_server[i].func(e, msg);
			return ;
		}
		i++;
	}
	cmd_server_unknown(msg);
}

void	cmd_server_unknown(t_protocol *msg)
{
	char	*str;
	char	*chr;
	char	*tmp;

	if (!msg->command || !msg->command[0])
	{
		write_log("warning", "no command");
		return ;
	}
	str = protocol_to_string(*msg);
	tmp = str;
	chr = ft_strstr(str, "\r\n");
	if (chr)
		*chr = 0;
	if (str && str[0] == ':')
	{
		chr = ft_strstr(str, " ");
		if (chr)
			str = chr + 1;
	}
	ft_printf("[server] : %s\n", str);
	free(tmp);
}

void	cmd_join_server(t_client *e, t_protocol *msg)
{
	char	*user;

	if (msg && msg->prefix && msg->params[0] && msg->params
		&& msg->params[0] && msg->params[0][0])
	{
		user = extract_nick_prefix(msg->prefix);
		ft_printf("\033[32m[join]\033[0m %s join %s\n", user, msg->params[0]);
		if (e->chan)
			free(e->chan);
		if (user)
			free(user);
		e->chan = ft_strdup(msg->params[0]);
	}
}

void	cmd_quit_server(t_client *e, t_protocol *msg)
{
	char	*user;

	e = e + 0;
	if (msg && msg->prefix)
	{
		user = extract_nick_prefix(msg->prefix);
		ft_printf("\033[31m[quit]\033[0m %s disconnected from server\n", user);
		if (user)
			free(user);
	}
}
