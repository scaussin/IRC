#include <stdio.h>
#include <sys/socket.h>
#include "bircd.h"

void	client_write(t_env *e, int cs)
{
	char	*data;
	int		ret_send;

	data = read_buf(e->fds[cs].buf_write);
	ret_send = send(cs, data, e->fds[cs].buf_write.len, 0);
	if (ret_send > 0)
	{
		e->fds[cs].buf_write.start = (e->fds[cs].buf_write.start + ret_send) % BUF_SIZE;
		e->fds[cs].buf_write.len -= ret_send;
	}
}
