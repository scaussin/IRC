/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 18:24:51 by scaussin          #+#    #+#             */
/*   Updated: 2016/07/31 23:17:57 by scaussin         ###   ########.fr       */
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
	}
}

void	cmd_nick_server(t_client *e, t_protocol *msg)
{
	msg = msg + 0;
	e->nick[0] = 0;
	write_log("warning", "nickname is already in use");
	ft_printf("Enter your nickname : ");
}

void	cmd_already_registered_server(t_client *e, t_protocol *msg)
{
	msg = msg + 0;
	e = e + 0;
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

/*
void	parser(t_env *e, int cs, t_protocol msg)
{
	int			i;
	char		*str_protocol;

	i = 0;
	str_protocol = protocol_to_string(msg);
	ft_printf("in <= %s", str_protocol);
	free(str_protocol);
	while (i < SIZE_PTR_FUNC)
	{
		if (!ft_strcmp(msg.command, e->ptr_func[i].name))
		{
			e->ptr_func[i].func(e, cs, msg);
			return ;
		}
		i++;
	}
	cmd_unknown(e, cs, msg);
}
*/
