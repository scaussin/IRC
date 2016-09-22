/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 11:02:02 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/21 11:55:28 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	cmd_names(t_env *e, int cs, t_protocol msg)
{
	char	**params_end;

	msg = *(&msg);
	params_end = malloc_params(2);
	ft_strcpy(params_end[0], e->fds[cs].nick);
	if (e->fds[cs].chan)
	{
		send_lst_names(e, cs, get_clients_on_chan(e, e->fds[cs].chan));
		ft_strcpy(params_end[1], e->fds[cs].chan);
	}
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

	/*i = 0;
	params_list = malloc_params(7);
	ft_strcpy(params_list[0], e->fds[cs].nick);
	ft_strcpy(params_list[1], e->fds[cs].chan);*/
	params_list = send_lst_who_2(&i, e->fds[cs].nick, e->fds[cs].chan);
	while (clients_on_chan && clients_on_chan[i])
	{
		ft_strcpy(params_list[2], clients_on_chan[i]->name);
		ft_strcpy(params_list[3], clients_on_chan[i]->host);
		ft_strcpy(params_list[4], NAME_SERVER);
		ft_strcpy(params_list[5], clients_on_chan[i]->nick);
		ft_strcpy(params_list[6], "H@");
		trailer = (char *)Xv(NULL, malloc(ft_strlen(clients_on_chan[i]->name +
			3)), "malloc");
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

char	**send_lst_who_2(int *i, char *nick, char *chan)
{
	char **params_list;

	*i = 0;
	params_list = malloc_params(7);
	ft_strcpy(params_list[0], nick);
	ft_strcpy(params_list[1], chan);
	return (params_list);
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