/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 20:34:56 by scaussin          #+#    #+#             */
/*   Updated: 2016/05/19 18:47:51 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	cmd_privmsg(t_env *e, int cs, t_protocol msg)
{
	char	**params;

	if (msg.params && msg.params[0] && msg.params[0][0]
		&& msg.trailer && msg.trailer[0])
	{
		if (e->fds[cs].chan)
		{
			if (msg.params[0][0] == '#')
				privmsg_to_chan(e, cs, msg.params, msg.trailer);
			else
				privmsg_to_client(e, cs, msg.params[0], msg.trailer);
		}
		else
		{
			params = malloc_params(1);
			ft_strcpy(params[0], e->fds[cs].nick);
			send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"NOTICE", params, "Not on channel. Use /join <#chan>"));
			free_params(params);
		}
	}
}

void	privmsg_to_chan(t_env *e, int cs, char **chan_dest, char *msg_to_send)
{
	char	*prefix;

	prefix = gen_prefix(e->fds[cs]);
	send_to_chan_exept_sender(e, cs,
		fill_protocol(prefix, "PRIVMSG", chan_dest, msg_to_send));
	free(prefix);
}

int		privmsg_to_client(t_env *e, int cs, char *nick_dest, char *msg_to_send)
{
	char	**params;
	char	*prefix;
	int		return_flag;
	t_fd	*dest_client;

	prefix = gen_prefix(e->fds[cs]);
	params = malloc_params(1);
	ft_strcpy(params[0], nick_dest);
	dest_client = get_client_by_nick(e, cs, nick_dest);
	if (dest_client && !ft_strcmp(dest_client->chan, e->fds[cs].chan))
	{
		send_protocol_to_client(dest_client,
			fill_protocol(prefix, "PRIVMSG", params, msg_to_send));
		return_flag = 1;
	}
	else
		return_flag = -1;
	free_params(params);
	free(prefix);
	return (return_flag);
}

t_fd	*get_client_by_nick(t_env *e, int cs, char *nick)
{
	int		i;
	char	**params;

	i = 0;
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT_REGISTER
			&& !ft_strcmp(e->fds[i].nick, nick))
			return (&(e->fds[i]));
		i++;
	}
	params = malloc_params(1);
	ft_strcpy(params[0], e->fds[cs].nick);
	send_protocol_to_client(&(e->fds[cs]), fill_protocol(NAME_SERVER,
		"401", params, "No such nick."));
	free_params(params);
	return (NULL);
}


