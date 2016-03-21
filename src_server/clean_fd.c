
#include <stdlib.h>
#include "bircd.h"

void	clean_fd(t_fd *fd)
{
	ft_bzero(fd, sizeof(t_fd));
	fd->type = FD_FREE;
}
