/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 18:30:00 by scaussin          #+#    #+#             */
/*   Updated: 2016/04/24 22:16:32 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	cmd_names(t_env *e, int cs, t_protocol msg)
{
	char	**params_end;

	if (e->fds[cs].chan && msg.params && msg.params[0]
		&& !ft_strcmp(msg.params[0], e->fds[cs].chan))
		send_lst_names(e, cs, get_clients_on_chan(e, e->fds[cs].chan));
	params_end = malloc_params(2);
	ft_strcpy(params_end[0], e->fds[cs].nick);
	ft_strcpy(params_end[1], msg.params[0]);
	send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
		"366", params_end, "End of /NAMES list."));
	free_params(params_end);
}

void	cmd_users(t_env *e, int cs, t_protocol msg)
{
	msg = *(&msg);
	send_protocol_to_client(&e->fds[cs], 
		fill_protocol(NAME_SERVER, "446", NULL,
			"cmd USERS disabled"));
}

void	cmd_who(t_env *e, int cs, t_protocol msg)
{
	char	**params_end;

	if (e->fds[cs].chan && msg.params
		&& str_equal(msg.params[0], e->fds[cs].chan))
	{
		send_lst_who(e, cs, get_clients_on_chan(e, e->fds[cs].chan));
	}
	params_end = malloc_params(2);
	ft_strcpy(params_end[0], e->fds[cs].nick);
	ft_strcpy(params_end[1], e->fds[cs].chan);
	send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
		"315", params_end, "End of /WHO list."));
	free_params(params_end);
}

void	send_lst_who(t_env *e, int cs, t_fd **clients_on_chan)
{
	int		i;
	char	**params_list;
	char	*trailer;

	i = 0;
	params_list = malloc_params(7);
	ft_strcpy(params_list[0], e->fds[cs].nick);
	ft_strcpy(params_list[1], e->fds[cs].chan);
	while (clients_on_chan && clients_on_chan[i])
	{
		ft_strcpy(params_list[2], clients_on_chan[i]->name);
		ft_strcpy(params_list[3], clients_on_chan[i]->host);
		ft_strcpy(params_list[4], NAME_SERVER);
		ft_strcpy(params_list[5], clients_on_chan[i]->nick);
		ft_strcpy(params_list[6], "H@");
		trailer = (char *)Xv(NULL, malloc(ft_strlen(clients_on_chan[i]->name + 3)), "malloc");
		ft_strcpy(trailer, "0 ");
		ft_strcat(trailer, clients_on_chan[i]->name);
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"352", params_list, clients_on_chan[i]->nick));
		free(trailer);
		i++;
	}
	free_params(params_list);
	if (clients_on_chan)
		free(clients_on_chan);
}

void	send_lst_names(t_env *e, int cs, t_fd **clients_on_chan)
{
	int		i;
	char	**params_list;

	i = 0;
	params_list = malloc_params(3);
	ft_strcpy(params_list[0], e->fds[cs].nick);
	ft_strcpy(params_list[1], "=");
	ft_strcpy(params_list[2], e->fds[cs].chan);
	while (clients_on_chan && clients_on_chan[i])
	{
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"353", params_list, clients_on_chan[i]->nick));
		i++;
	}
	free_params(params_list);
	if (clients_on_chan)
		free(clients_on_chan);
}

t_fd	**get_clients_on_chan(t_env *e, char *chan)
{
	int		i;
	int		j;
	t_fd	**lst_client;

	i = 0;
	j = 0;
	lst_client = (t_fd **)Xv(NULL, malloc((e->max + 1) * sizeof(t_fd *)), 
		"malloc");
	ft_bzero(lst_client, (e->max + 1) * sizeof(t_fd *));
	while (i <= e->max)
	{
		if (str_equal(e->fds[i].chan, chan)
			&& e->fds[i].type == FD_CLIENT_REGISTER)
		{
			lst_client[j] = &(e->fds[i]);
			j++;
		}
		i++;
	}
	return (lst_client);
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

void	cmd_away(t_env *e, int cs, t_protocol msg)/**/
{
	char	*tmp;
	char	*str;

	msg = *(&msg);
	str = ft_strjoin(":irc_scaussin 305 ", e->fds[cs].nick);/*server name*/
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
	if (e->fds[cs].name)
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"462", NULL, "Your are already registred"));
	else if (msg.params && msg.params[0] && msg.params[0][0])
	{
		e->fds[cs].name = ft_strdup(msg.params[0]);
		register_client(&e->fds[cs]);
	}
	else
	{
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"461", NULL, "need username"));
	}
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
