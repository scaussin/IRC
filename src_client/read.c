/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 00:25:39 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/28 12:13:02 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"
#include <errno.h>
#include <sys/socket.h>

int		read_circular(t_ring_buf *buf_read, int cs)
{
	int		ret;
	char	*buf_tmp;
	int		size_read;

	size_read = BUF_SIZE - buf_read->len;
	if (size_read == 0)
		write_log("error", "buf read full");
	buf_tmp = (char *)XV(NULL, malloc(size_read), "malloc");
	while (1)
	{
		if (cs == 0)
			ret = read(0, buf_tmp, size_read);
		else
			ret = recv(cs, buf_tmp, size_read, 0);
		if (ret == -1 && (errno == EAGAIN || errno == EINTR))
			continue;
		else
			break ;
	}
	if (ret == -1)
		write_log("warning", "receive");
	write_buf(buf_read, buf_tmp, ret);
	free(buf_tmp);
	return (ret);
}

void	read_server(t_client *e, int cs)
{
	t_protocol	msg;

	if (read_circular(&e->buf_read_server, cs) <= 0)
	{
		if (e->leaving == 0)
			write_log("warning", "socket closed");
		close_connection(e);
	}
	else
	{
		while (lexer_server(&msg, &e->buf_read_server) == 1)
		{
			parsing_server(e, &msg);
			free_protocol(msg);
		}
	}
}

void	read_client(t_client *e, int cs)
{
	int					r;
	t_parsing_client	msg;

	r = read_circular(&e->buf_read_client, cs);
	if (r > 0)
	{
		ft_bzero(&msg, sizeof(t_parsing_client));
		while (lexer_client(e, &msg) == 1)
		{
			parser_client(e, &msg);
			free_parsing_client(&msg);
		}
	}
}
