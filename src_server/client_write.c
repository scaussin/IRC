#include <stdio.h>
#include <sys/socket.h>
#include "bircd.h"

void	client_write(t_env *e, int cs)
{
	printf("#%d [%s]", cs, e->fds[cs].buf_read);
}
