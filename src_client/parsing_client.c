/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 20:20:04 by scaussin          #+#    #+#             */
/*   Updated: 2016/06/03 18:58:29 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

void	parser_client(t_client *e, t_parsing_client *msg)
{
	int	i;

	i = 0;
	//ft_printf("parser : %s - %s\n", msg->command, msg->data);
	if (manage_nick(e, msg) <= 0)
		return ;
	if (msg->command)
	{
		while (i < NB_PTR_FUNC_CLIENT)
		{
			if (str_equal(e->func_client[i].name, msg->command))
			{
				e->func_client[i].func(e, msg);
				return ;
			}
			i++;
		}
		send_row_cmd_client(e, msg);
	}
	else if (msg->data)
	{
		cmd_privmsg_client(e, msg);
	}
}

void	send_row_cmd_client(t_client *e, t_parsing_client *msg)
{
	int		i;
	char	*(params[2]);

	i = 1;
	params[0] = msg->data;
	params[1] = NULL;
	while (msg->command[i])
	{
		msg->command[i]	= ft_toupper(msg->command[i]);
		i++;
	}
	send_protocol_to_server(e,
		fill_protocol(NULL, &msg->command[1], params, NULL));
}

void	cmd_leave_client(t_client *e, t_parsing_client *msg)
{
	char	*(params[2]);

	msg = msg + 0;
	params[0] = e->chan;
	params[1] = NULL;
	send_protocol_to_server(e,
		fill_protocol(NULL, "PART", params, NULL));
}

void	cmd_privmsg_client(t_client *e, t_parsing_client *msg)
{
	send_privmsg(e, e->chan, msg->data);
}

void	send_cmd_msg(t_client *e, t_parsing_client *msg)
{
	char	*esp;

	esp = ft_strchr(msg->data, ' ');
	if (esp && esp[1])
		*esp = 0;
	else
	{
		write_log("warning", "usage : /msg <pseudo> <msg>");
		return ;
	}
	send_privmsg(e, msg->data, &esp[1]);
}

void	send_privmsg(t_client *e, char *to, char *msg)
{
	char	*(params[2]);

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
