/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv_accept.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 12:24:34 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/28 12:24:42 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "bircd.h"

void			srv_accept(t_env *e, int s)
{
	int					cs;
	struct sockaddr_in	csin;
	socklen_t			csin_len;
	char				*tmp_port;

	csin_len = sizeof(csin);
	cs = X(-1, accept(s, (struct sockaddr*)&csin, &csin_len), "accept");
	printf("New client #%d from %s:%d\n", cs,
		inet_ntoa(csin.sin_addr), ntohs(csin.sin_port));
	clean_fd(&e->fds[cs]);
	tmp_port = ft_itoa(ntohs(csin.sin_port));
	e->fds[cs].host = (char *)XV(NULL, malloc(ft_strlen(inet_ntoa(
		csin.sin_addr)) + ft_strlen(tmp_port) + 2), "malloc");
	ft_strcpy(e->fds[cs].host, inet_ntoa(csin.sin_addr));
	ft_strcat(e->fds[cs].host, ":");
	ft_strcat(e->fds[cs].host, tmp_port);
	free(tmp_port);
	e->fds[cs].type = FD_CLIENT_NO_REGISTER;
	e->fds[cs].fct_read = client_read;
	e->fds[cs].fct_write = client_write;
	write_log(SUCCES_CLIENT_CONNECTED);
}
