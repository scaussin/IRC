/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 00:30:32 by scaussin          #+#    #+#             */
/*   Updated: 2016/05/22 01:18:25 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

void	init_fd(t_client *e)
{
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);

	FD_SET(0, &e->fd_read);
	e->max_select = 0;
	if (e->buf_write_client.len > 0)
	{
		FD_SET(1, &e->fd_write);
		e->max_select = MAX(e->max_select, 1);
	}
	if (e->socket != -1)
	{
		FD_SET(e->socket, &e->fd_read);
		e->max_select = MAX(e->max_select, e->socket);
		if (e->buf_write_server.len > 0)
		{
			FD_SET(e->socket, &e->fd_write);
			e->max_select = MAX(e->max_select, e->socket);
		}
	}
}

void	do_select(t_client *e)
{
	e->ret_select = select(e->max_select + 1, &e->fd_read, &e->fd_write, NULL, NULL);
}

void	check_fd(t_client *e)
{
	int	i;

	i = 0;
	while ((i <= e->max_select) && (e->ret_select > 0))
	{
		if (FD_ISSET(i, &e->fd_read))
		{
			if (i == 0)
				read_client(e, i);
			else
				read_server(e, i);
			e->ret_select--;
		}
		if (FD_ISSET(i, &e->fd_write))
		{
			if (i == 1)
				write_client(e, i);
			else
				write_server(e, i);
			e->ret_select--;
		}
		i++;
	}
}
