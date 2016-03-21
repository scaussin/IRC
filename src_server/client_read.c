
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include "bircd.h"

void	client_read(t_env *e, int cs)
{
	int	r;
	int	i;

	r = read_circular(&(e->fds[cs].buf_read), cs);
	if (r <= 0)
	{
		close(cs);
		clean_fd(&e->fds[cs]);
		printf("client #%d gone away\n", cs);
	}
	else
	{
		i = 0;
		while (i < e->maxfd)
		{
			if ((e->fds[i].type == FD_CLIENT) &&
				(i != cs))
				write_buf(&(e->fds[i].buf_write), read_buf(e->fds[cs].buf_read), e->fds[cs].buf_read.len);
			i++;
		}
	}
}

int		read_circular(t_ring_buf *buf_read, int cs)
{
	int		ret;
	char	*buf_tmp;
	int		size_read;

	size_read = BUF_SIZE - buf_read->len;
	buf_tmp = (char *)Xv(NULL, malloc(size_read), "malloc");
	ret = recv(cs, buf_tmp, size_read, 0);
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
		/*move start*/
		X(1, buf->len + size > BUF_SIZE, "write buffer overflow");
		while (i < size)
		{
			buf->data[(buf->start + buf->len + i) % BUF_SIZE] = to_write[i];
			i++;
		}
		buf->len += i;
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
