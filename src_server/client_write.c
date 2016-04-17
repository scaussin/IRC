#include <stdio.h>
#include <sys/socket.h>
#include "bircd.h"
#include <errno.h>

void	client_write(t_env *e, int cs)
{
	char	*data;
	int		ret_send;

	data = read_buf(e->fds[cs].buf_write);
	while (1)
	{
		ret_send = send(cs, data, e->fds[cs].buf_write.len, 0);
		if (ret_send == -1 && (errno == EAGAIN || errno == EINTR))
			continue;
		else
			break;
	}
	free(data);
	if (ret_send == -1)
		write_log(WARNING_SEND);
	if (ret_send > 0)
	{
		e->fds[cs].buf_write.start = (e->fds[cs].buf_write.start + ret_send) % BUF_SIZE;
		e->fds[cs].buf_write.len -= ret_send;
	}
}

void	send_str_to_client(t_fd *client, char *str)
{
	write_buf(&(client->buf_write), str, ft_strlen(str));
}

void	send_protocol_to_client(t_fd *client, t_protocol msg)
{
	char	*str;

	str = protocol_to_string(msg);
	write_buf(&(client->buf_write), str, ft_strlen(str));
	free(str);
}

void	send_protocol_to_chan(t_env *e, t_protocol msg, int cs)
{
	char	*str;
	int		i;

	i = 0;
	str = protocol_to_string(msg);
	if (!e->fds[cs].chan)
		write_buf(&e->fds[cs].buf_write, str, ft_strlen(str));
	else
	{
		while (i < e->maxfd)
		{
			if (e->fds[i].type == FD_CLIENT_REGISTER
				&& !ft_strcmp(e->fds[i].chan, e->fds[cs].chan))
				write_buf(&e->fds[i].buf_write, str, ft_strlen(str));
			i++;
		}
	}
	free(str);
}
