
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
			/*print_protocol(msg);
			ft_printf("msg: %s", protocol_to_string(msg));
			if (e->fds[cs].type == FD_CLIENT_NO_REGISTER)
				register_client(&e->fds[cs], msg);
			else
				send_str_to_client(&e->fds[cs], ":serv_IRC PRIVMSG scaussin :bonjour\r\n");*/
		}
	}
	/*if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
		write_log(SUCCES_CLIENT_DISCONNECTED);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if (e->fds[i].type == FD_CLIENT_REGISTER && i != cs)
				write_buf(&(e->fds[i].buf_write),
					read_buf(e->fds[cs].buf_read), e->fds[cs].buf_read.len);//free
			i++;
		}
		e->fds[cs].buf_read.len = 0;
	}*/
}

void	close_connection(t_env *e, int cs)
{
	if (e->fds[cs].type == FD_CLIENT_CLOSE)
		write_log(SUCCES_CLIENT_DISCONNECTED);
	else
		write_log(WARNING_CLIENT_LOST);
	FD_CLR(cs, &e->fd_write);
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
