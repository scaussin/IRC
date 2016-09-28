/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 18:30:00 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/21 11:17:23 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	cmd_quit(t_env *e, int cs, t_protocol msg)
{
	msg = *(&msg);
	e->fds[cs].type = FD_CLIENT_CLOSE;
}

t_fd	**get_clients_on_chan(t_env *e, char *chan)
{
	int		i;
	int		j;
	t_fd	**lst_client;

	i = 0;
	j = 0;
	lst_client = (t_fd **)XV(NULL, malloc((e->max + 1) * sizeof(t_fd *)),
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

	trailer = (char *)XV(NULL, malloc(BUF_SIZE), "malloc");
	ft_strcpy(trailer, "command ");
	ft_strcat(trailer, msg.command);
	ft_strcat(trailer, " uncknown");
	send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER, "421",
		NULL, trailer));
	free(trailer);
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
