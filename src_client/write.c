/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 00:28:50 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/28 12:18:48 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"
#include <errno.h>
#include <sys/socket.h>

void	send_server(t_ring_buf *buf, int cs)
{
	char	*data;
	int		ret_send;

	data = read_buf(*buf);
	while (1)
	{
		ret_send = send(cs, data, buf->len, MSG_DONTWAIT);
		if (ret_send == -1 && (errno == EAGAIN || errno == EINTR))
			continue;
		else
			break ;
	}
	free(data);
	if (ret_send == -1)
		write_log("warning", "send");
	update_offset_buf(buf, ret_send);
}

void	send_protocol_to_server(t_client *e, t_protocol msg)
{
	char	*str;

	str = protocol_to_string(msg);
	write_buf(&e->buf_write_server, str, ft_strlen(str));
	free(str);
}

void	write_server(t_client *e, int cs)
{
	send_server(&e->buf_write_server, cs);
	if (e->leaving == 1)
		close_connection(e);
}

void	write_client(t_client *e, int cs)
{
	char	*read;
	int		ret_write;

	cs = *&cs;
	read = read_buf(e->buf_write_client);
	ret_write = write(1, read, e->buf_write_client.len);
	update_offset_buf(&e->buf_write_client, ret_write);
	free(read);
}
