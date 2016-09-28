/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_client_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 09:53:46 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/28 12:01:32 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

void	cmd_disconnect(t_client *e, t_parsing_client *msg)
{
	cmd_quit(e, msg);
}

void	cmd_quit(t_client *e, t_parsing_client *msg)
{
	ft_printf("cmd_quit\n");
	msg = msg + 0;
	send_protocol_to_server(e,
		fill_protocol(NULL, "QUIT", NULL, NULL));
	e->leaving = 1;
}

void	cmd_connect(t_client *e, t_parsing_client *msg)
{
	char	**split;

	if (msg->data)
	{
		split = ft_strsplit(msg->data, ' ');
		if (ft_strlen_2d(split) == 2)
		{
			if (e->socket != -1)
			{
				send_protocol_to_server(e,
					fill_protocol(NULL, "QUIT", NULL, NULL));
				close_connection(e);
			}
			init_client(e);
			connect_to_srv(e, split[0], ft_atoi(split[1]));
			free_tab_2d(split);
			return ;
		}
		free_tab_2d(split);
	}
	ft_printf("usage : /connect <ip> <port>\n");
}

void	send_privmsg(t_client *e, char *to, char *msg)
{
	char	*(params[2]);
	char	*default_chan;

	default_chan = "irc_scaussin";
	if (!to)
		to = default_chan;
	params[0] = to;
	params[1] = NULL;
	send_protocol_to_server(e,
		fill_protocol(NULL, "PRIVMSG", params, msg));
}

int		manage_nick(t_client *e, t_parsing_client *msg)
{
	if (e->socket != -1 && e->nick[0] == 0)
	{
		if (msg->command || ft_strlen(msg->data) > MAX_LEN_NICK
			|| !str_isalnum(msg->data))
		{
			ft_printf("Enter your nickname : ");
			return (-1);
		}
		else
		{
			ft_strcpy(e->nick, msg->data);
			auth_irc(e);
			return (0);
		}
	}
	return (1);
}
