
#include <stdlib.h>
#include "bircd.h"

void	clean_fd(t_fd *fd)
{
	if (fd->host)
		free(fd->host);
	if (fd->name)
		free(fd->name);
	if (fd->chan)
		free(fd->chan);
	ft_bzero(fd, sizeof(t_fd));
	fd->type = FD_FREE;
}
