/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 00:31:26 by scaussin          #+#    #+#             */
/*   Updated: 2016/07/31 22:12:23 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "client_irc.h"

int		connect_to_srv(t_client *e, char *addr, int port)
{
	int					s;
	struct sockaddr_in	sin;
	struct protoent		*pe;
	struct hostent		*host;

	if ((host = gethostbyname(addr)))
		addr = inet_ntoa(*((struct in_addr **)(host->h_addr_list))[0]);

	pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), "getprotobyname");
	s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(addr);
	sin.sin_port = htons(port);
	if (connect(s, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		write_log("warning", "connection fail");
		return (-1);
	}
	e->socket = s;
	e->host = ft_strdup(addr);
	ft_printf("\033[32mConnected\033[0m %s:%d\nEnter your nickname : ", addr, port);
	return (1);
}

void	auth_irc(t_client *e)
{
	char	**params;

	params = malloc_params(3);
	ft_strcpy(params[0], e->nick);
	ft_strcpy(params[1], "*");
	ft_strcpy(params[2], e->host);
	send_protocol_to_server(e, fill_protocol(NULL, "USER", params, e->nick));
	ft_strcpy(params[1], 0);
	send_protocol_to_server(e, fill_protocol(NULL, "NICK", params, NULL));
	free_params(params);
}

void	close_connection(t_client *e)
{
	e = e + 0;
	/*
	if (FD_ISSET(cs, &e->fd_write))
	{
		FD_ZERO(&e->fd_write);
		e->r--;
	}
	*/
	close(e->socket);
	init_client(e);
	ft_printf("\033[31m[quit]\033[0m You are disconnected\n");
}
