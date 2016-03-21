#ifndef BIRCD_H_
# define BIRCD_H_

# include <sys/select.h>
# include "libft.h"

# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2

# define BUF_SIZE	4096
# define NAME_SIZE	32

# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))
# define MAX(a,b)	((a > b) ? a : b)

# define USAGE		"Usage: %s port\n"

typedef struct	s_ring_buf
{
	int			start;
	int			len;
	char		data[BUF_SIZE];
}				t_ring_buf;

typedef struct	s_fd
{
	int			type;
	char		nick[NAME_SIZE + 1];
	char		chan[NAME_SIZE + 1];
	void		(*fct_read)();
	void		(*fct_write)();
	t_ring_buf	buf_read;
	t_ring_buf	buf_write;
}				t_fd;

typedef struct	s_env
{
	t_fd		*fds;
	int			port;
	int			maxfd;
	int			max;
	int			r;
	fd_set		fd_read;
	fd_set		fd_write;
}				t_env;

void	init_env(t_env *e);
void	get_opt(t_env *e, int ac, char **av);
void	main_loop(t_env *e);
void	srv_create(t_env *e, int port);
void	srv_accept(t_env *e, int s);
void	client_read(t_env *e, int cs);
void	client_write(t_env *e, int cs);
void	clean_fd(t_fd *fd);
int		x_int(int err, int res, char *str, char *file, int line);
void	*x_void(void *err, void *res, char *str, char *file, int line);
void	init_fd(t_env *e);
void	do_select(t_env *e);
void	check_fd(t_env *e);

char	*read_buf(t_ring_buf buf);
void	write_buf(t_ring_buf *buf, char *to_write, int size);
int		read_circular(t_ring_buf *buf_read, int cs);

void	print_buf(t_ring_buf buf);

#endif /* !BIRCD_H_ */
