/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 00:06:26 by scaussin          #+#    #+#             */
/*   Updated: 2016/04/25 00:18:06 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	cmd_nick(t_env *e, int cs, t_protocol msg)
{
	char	*prefix_tmp;
	char	*new_nick;

	if (check_error_nick(e, cs , msg, &new_nick) == 1)
	{
		if (e->fds[cs].type == FD_CLIENT_REGISTER)
		{
			prefix_tmp = gen_prefix(e->fds[cs]);
			send_protocol_to_chan(e, cs, fill_protocol(prefix_tmp,
			"NICK", NULL, new_nick));
			free(prefix_tmp);
		}
		ft_strcpy(e->fds[cs].nick, new_nick);
		register_client(&e->fds[cs]);
	}		
}

int		check_error_nick(t_env *e, int cs, t_protocol msg, char **new_nick)
{
	if ((msg.params && (*new_nick = msg.params[0]) && msg.params[0][0]) 
		|| (*new_nick = msg.trailer))
	{
		if (ft_strlen(*new_nick) <= MAX_LEN_NICK)
			return (check_nick_in_use(e, cs, *new_nick));
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"432", NULL, "9 characters maximum"));
		return (-1);
	}
	else
	{
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"431", NULL, "No nickname given."));
		return (-1);
	}
}

int		check_nick_in_use(t_env *e, int cs, char *new_nick)
{
	int		i;
	char	**tmp_params;

	i = 0;
	while (i < e->maxfd)
	{
		if (!ft_strcmp(e->fds[i].nick, new_nick))
		{
			if (i == cs)
				return (0);
			tmp_params = malloc_params(2);
			ft_strcpy(tmp_params[0], e->fds[i].nick);
			ft_strcpy(tmp_params[1], new_nick);
			send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"433", tmp_params, "Nickname is already in use."));
			free_params(tmp_params);
			return (-1);
		}
		i++;
	}
	return (1);
}

void	register_client(t_fd *client)
{
	char	**params;
	//char	*trailer;

	if (client->type == FD_CLIENT_NO_REGISTER && client->name && client->nick[0])
	{
		ft_printf("Client [%s] accepted\n", client->nick);
		/*send_str_to_client(client, ":127.0.0.1 001 scaussin :Welcome
		:127.0.0.1 002 scaussin :Your host is irc_scaussin, running version 1
		:127.0.0.1 003 scaussin :This server was created
		:127.0.0.1 004 scaussin irc_scaussin
		:127.0.0.1 005 scaussin irc_scaussin
		:127.0.0.1 005 scaussin irc_scaussin
		:127.0.0.1 NOTICE scaussin :Bonjour
		");*/
		params = malloc_params(1);
		ft_strcpy(params[0], client->nick);
		//trailer = (char *)Xv(NULL, malloc(BUF_SIZE), "malloc");
		//ft_strcpy(ft_strcpy, "");
		send_protocol_to_client(client, fill_protocol(NAME_SERVER, "001", params, "Welcome to the irc_scaussin"));
		send_protocol_to_client(client, fill_protocol(NAME_SERVER, "002", params, "Your host is irc_scaussin, running version 1"));
		send_protocol_to_client(client, fill_protocol(NAME_SERVER, "003", params, "This server was created Today"));
		send_protocol_to_client(client, fill_protocol(NAME_SERVER, "004", params, NULL));
		send_protocol_to_client(client, fill_protocol(NAME_SERVER, "005", params, NULL));
		send_protocol_to_client(client, fill_protocol(NAME_SERVER, "251", params, "There are 22 users and 31421 invisible on 47 servers"));
		send_protocol_to_client(client, fill_protocol(NAME_SERVER, "252", params, "operator(s) online"));
		send_protocol_to_client(client, fill_protocol(NAME_SERVER, "NOTICE", params, "Welcome"));

		/*send_str_to_client(client, "
		:irc_scaussin 001 scaussin :Welcome to the QuakeNet IRC Network, scaussin
		:irc_scaussin 002 scaussin :Your host is euroserv.fr.quakenet.org, running version u2.10.12.10+snircd(1.3.4a)
		:irc_scaussin 003 scaussin :This server was created Tue Nov 18 2014 at 18:46:36 CET
		:irc_scaussin 004 scaussin euroserv.fr.quakenet.org u2.10.12.10+snircd(1.3.4a) dioswkgxRXInP biklmnopstvrDcCNuMT bklov
		:irc_scaussin 005 scaussin WHOX WALLCHOPS WALLVOICES USERIP CPRIVMSG CNOTICE :are supported by this server
		:irc_scaussin 005 scaussin MAXNICKLEN=15 :are supported by this server
		:irc_scaussin 251 scaussin :There are 22 users and 31421 invisible on 47 servers
		:irc_scaussin 252 scaussin 69 :operator(s) online
		:irc_scaussin NOTICE scaussin :on 1 ca 1(4) ft 20(20)
		");*/
		client->type = FD_CLIENT_REGISTER;
		free_params(params);
	}
}
