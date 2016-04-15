/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 18:30:00 by scaussin          #+#    #+#             */
/*   Updated: 2016/04/15 18:00:49 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	init_ptr_func(t_ptr_func *ptr_func)
{
	ptr_func[0].name = "USER";
	ptr_func[0].func = cmd_user;
	ptr_func[1].name = "NICK";
	ptr_func[1].func = cmd_nick;
	ptr_func[2].name = "PING";
	ptr_func[2].func = cmd_ping;
	ptr_func[3].name = "PRIVMSG";
	ptr_func[3].func = cmd_privmsg;
	ptr_func[4].name = "AWAY";
	ptr_func[4].func = cmd_away;
}

void	cmd_unknown(t_env *e, int cs, t_protocol msg)
{
	char	*trailer;

	trailer = (char *)Xv(NULL, malloc(BUF_SIZE), "malloc");
	ft_strcpy(trailer, "command ");
	ft_strcat(trailer, msg.command);
	ft_strcat(trailer, " uncknown");
	send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER, "421", NULL, trailer));
	free(trailer);
}

void	cmd_away(t_env *e, int cs, t_protocol msg)
{
	char	*tmp;
	char	*str;

	msg = *(&msg);
	str = ft_strjoin(":irc_scaussin 305 ", e->fds[cs].nick);
	tmp = str;
	str = ft_strjoin(str, " :You are no longer marked as being away\r\n");
	free(tmp);
	send_str_to_client(&e->fds[cs], str);
	free(str);
}

void	cmd_privmsg(t_env *e, int cs, t_protocol msg)
{
	char	*tmp;
	char	*str;

	str = ft_strjoin(":irc_scaussin PRIVMSG scaussin :", msg.trailer);
	tmp = str;
	str = ft_strjoin(str, "\r\n");
	free(tmp);
	send_str_to_client(&e->fds[cs], str);
	free(str);
}

void	cmd_user(t_env *e, int cs, t_protocol msg)
{
	if (msg.params && msg.params[0] && msg.params[0][0])
	{
		e->fds[cs].name = ft_strdup(msg.params[0]);
		register_client(&e->fds[cs]);
	}
	else
		send_str_to_client(&e->fds[cs], "ERR_NEEDMOREPARAMS :need username\r\n");
}

void	cmd_nick(t_env *e, int cs, t_protocol msg)
{
	if (msg.params && msg.params[0] && msg.params[0][0])
	{
		e->fds[cs].nick = ft_strdup(msg.params[0]);
		register_client(&e->fds[cs]);
	}
	else
		send_str_to_client(&e->fds[cs], "ERR_NONICKNAMEGIVEN :need nickname\r\n");
	/*doublon*/
}

void	cmd_ping(t_env *e, int cs, t_protocol msg)
{
	char	*tmp;
	char	*str;

	str = ft_strjoin("PONG :", msg.trailer);
	tmp = str;
	str = ft_strjoin(str, "\r\n");/*timestamp*/
	free(tmp);
	send_str_to_client(&e->fds[cs], str);
	free(str);
}

void	register_client(t_fd *client)
{
	if (client->type == FD_CLIENT_NO_REGISTER && client->name && client->nick)
	{
		ft_printf("Client [%s] accepted\n", client->nick);
		//send_str_to_client(client, ":127.0.0.1 001 scaussin :Welcome\r\n:127.0.0.1 002 scaussin :Your host is irc_scaussin, running version 1\r\n:127.0.0.1 003 scaussin :This server was created\r\n:127.0.0.1 004 scaussin irc_scaussin\r\n:127.0.0.1 005 scaussin irc_scaussin\r\n:127.0.0.1 005 scaussin irc_scaussin\r\n:127.0.0.1 NOTICE scaussin :Bonjour\r\n");
		send_str_to_client(client, ":irc_scaussin 001 scaussin :Welcome to the QuakeNet IRC Network, scaussin\r\n:irc_scaussin 002 scaussin :Your host is euroserv.fr.quakenet.org, running version u2.10.12.10+snircd(1.3.4a)\r\n:irc_scaussin 003 scaussin :This server was created Tue Nov 18 2014 at 18:46:36 CET\r\n:irc_scaussin 004 scaussin euroserv.fr.quakenet.org u2.10.12.10+snircd(1.3.4a) dioswkgxRXInP biklmnopstvrDcCNuMT bklov\r\n:irc_scaussin 005 scaussin WHOX WALLCHOPS WALLVOICES USERIP CPRIVMSG CNOTICE SILENCE=15 MODES=6 MAXCHANNELS=20 MAXBANS=45 NICKLEN=15 :are supported by this server\r\n:irc_scaussin 005 scaussin MAXNICKLEN=15 TOPICLEN=250 AWAYLEN=160 KICKLEN=250 CHANNELLEN=200 MAXCHANNELLEN=200 CHANTYPES=#& PREFIX=(ov)@+ STATUSMSG=@+ CHANMODES=b,k,l,imnpstrDducCNMT CASEMAPPING=rfc1459 NETWORK=QuakeNet :are supported by this server\r\n:irc_scaussin 251 scaussin :There are 22 users and 31421 invisible on 47 servers\r\n:irc_scaussin 252 scaussin 69 :operator(s) online\r\n:irc_scaussin NOTICE scaussin :on 1 ca 1(4) ft 20(20)\r\n");
		client->type = FD_CLIENT_REGISTER;
	}
}