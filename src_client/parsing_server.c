/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/03 18:24:51 by scaussin          #+#    #+#             */
/*   Updated: 2016/06/03 19:25:28 by scaussin         ###   ########.fr       */
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
	e = e + 0;
	if (!msg->params || !msg->params[0] || !msg->params[0][0])
	{
		write_log("warning", "error params PRIVMSG");
		return ;
	}
	if (msg->trailer)
		ft_printf("[%s] : %s\n", msg->params[0], msg->trailer);
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
