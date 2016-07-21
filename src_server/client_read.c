/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 11:14:42 by scaussin          #+#    #+#             */
/*   Updated: 2016/05/21 01:10:18 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"
#include <errno.h>

void	client_read(t_env *e, int cs)
{
	int			r;
	t_protocol	msg;

	r = read_circular(&(e->fds[cs].buf_read), cs);
	if (r <= 0)
		close_connection(e, cs);
	else
	{
		while (lexer(&msg, &(e->fds[cs].buf_read)) == 1)
		{
			parser(e, cs, msg);
			free_protocol(msg);
		}
	}
}

void	close_connection(t_env *e, int cs)
{
	char	*tmp_prefix;

	if (e->fds[cs].type == FD_CLIENT_CLOSE)
	{
		tmp_prefix = gen_prefix(e->fds[cs]);
		send_protocol_to_chan(e, cs, fill_protocol(tmp_prefix,
		"QUIT", NULL, "Disconnected"));
		free(tmp_prefix);
		write_log(SUCCES_CLIENT_DISCONNECTED);
	}
	else
	{
		tmp_prefix = gen_prefix(e->fds[cs]);
		send_protocol_to_chan(e, cs, fill_protocol(tmp_prefix,
		"QUIT", NULL, "Connection lost"));
		free(tmp_prefix);
		write_log(WARNING_CLIENT_LOST);
	}
	if (FD_ISSET(cs, &e->fd_write))
	{
		FD_ZERO(&e->fd_write);
		e->r--;
	}
	close(cs);
	clean_fd(&e->fds[cs]);
}

int		read_circular(t_ring_buf *buf_read, int cs)
{
	int		ret;
	char	*buf_tmp;
	int		size_read;

	size_read = BUF_SIZE - buf_read->len;
	if (size_read == 0)
		write_log(ERROR_BUFFER_READ_FULL);
	buf_tmp = (char *)Xv(NULL, malloc(size_read), "malloc");
	while (1)
	{
		ret = recv(cs, buf_tmp, size_read, 0);
		if (ret == -1 && (errno == EAGAIN || errno == EINTR))
			continue;
		else
			break;
	}
	if (ret == -1)
		write_log(WARNING_RECEIVE);
	write_buf(buf_read, buf_tmp, ret);
	free(buf_tmp);
	return (ret);
}

void	write_buf(t_ring_buf *buf, char *to_write, int size)
{
	int		i;

	if (size)
	{
		i = 0;
		if (buf->len + size > BUF_SIZE)
			write_log(WARNING_BUFFER_FULL);
		else
		{
			while (i < size)
			{
				buf->data[(buf->start + buf->len + i) % BUF_SIZE] = to_write[i];
				i++;
			}
			buf->len += i;
		}
	}
}

char	*read_buf(t_ring_buf buf)
{
	char	*ret_data;
	int		i;

	ret_data = NULL;
	if (buf.len > 0)
	{
		ret_data = (char *)Xv(NULL, malloc(buf.len + 1), "malloc");
		ft_bzero(ret_data, buf.len + 1);
		i = 0;
		while (i < buf.len)
		{
			ret_data[i] = buf.data[(buf.start + i) % BUF_SIZE];
			i++;
		}
	}
	return (ret_data);
}
