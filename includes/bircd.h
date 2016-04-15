#ifndef BIRCD_H_
# define BIRCD_H_

# include <sys/select.h>
# include "libft.h"

# define FD_FREE				0
# define FD_SERV				1
# define FD_CLIENT_REGISTER		2
# define FD_CLIENT_NO_REGISTER	3
# define FD_CLIENT_CLOSE		4

# define BUF_SIZE				4096
# define MAX_SIZE_MSG_IRC		512
# define NAME_SIZE				9
# define SIZE_PTR_FUNC			5

# define END					"\r\n"
# define NAME_SERVER			"irc_scaussin"

# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))
# define MAX(a,b)	((a > b) ? a : b)
# define MIN(a,b)	((a < b) ? a : b)

# define USAGE		"Usage: %s port\n"

typedef enum	error_code
{
	SUCCES_CLIENT_CONNECTED,
	SUCCES_CLIENT_DISCONNECTED,

	ERROR_FATAL = 100,
	ERROR_BUFFER_WRITE_FULL,
	ERROR_BUFFER_READ_FULL,

	WARNING_CLIENT_LOST = 200,
	WARNING_RECEIVE,
	WARNING_MSG_IRC_TOO_LONG,
	WARNING_MSG_IRC_NOT_ENDING,
	WARNING_BUFFER_FULL,
	WARNING_SEND,
	WARNING_LEXER,
	WARNING_LEXER_NO_CMD,

	INFO = 300,
	INFO_ROOM_CREATED
}				e_error_code;

typedef struct	s_protocol
{
	char		*prefix;
	char		*command;
	char		**params;
	char		*trailer;
}				t_protocol;

typedef struct	s_ring_buf
{
	int			start;
	int			len;
	char		data[BUF_SIZE];
}				t_ring_buf;

typedef struct	s_fd
{
	int			type;
	char		*name;
	char		*nick;
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
	struct s_pt	*ptr_func;
	int			r;
	fd_set		fd_read;
	fd_set		fd_write;
}				t_env;

typedef struct	s_pt
{
	char		*name;
	void		(*func)(t_env *e, int cs, t_protocol msg);
}				t_ptr_func;

void	init_env(t_env *e);
void	get_opt(t_env *e, int ac, char **av);
void	main_loop(t_env *e);
void	srv_create(t_env *e, int port);
void	srv_accept(t_env *e, int s);
void	clean_fd(t_fd *fd);
void	init_fd(t_env *e);
void	do_select(t_env *e);
void	check_fd(t_env *e);

/*
** x.c
*/
void	*x_void(void *err, void *res, char *str, char *file, int line);
int		x_int(int err, int res, char *str, char *file, int line);
void	print_buf(t_ring_buf buf);
void	write_log(e_error_code error);

/*
** client_read.c
*/
void	client_read(t_env *e, int cs);
void	close_connection(t_env *e, int cs);
int		read_circular(t_ring_buf *buf_read, int cs);
void	write_buf(t_ring_buf *buf, char *to_write, int size);
char	*read_buf(t_ring_buf buf);

/*
** client_write.c
*/
void	client_write(t_env *e, int cs);
void	send_str_to_client(t_fd *client, char *str);
void	send_protocol_to_client(t_fd *client, t_protocol msg);

/*
** lexer.c
*/
int		lexer(t_protocol *msg, t_ring_buf *buf);
int		extract_prefix(char **prefix, char **msg);
int		extract_command(char **command, char **msg);
int		extract_params(char ***params, char **msg);
int		extract_trailer(char **trailer, char **msg);
int		check_error(char *line, char **end, t_ring_buf *buf);

/*
** parser.c
*/
void	parser(t_env *e, int cs, t_protocol msg);

/*
** protocol.c
*/
void	print_protocol(t_protocol msg);
char	*protocol_to_string(t_protocol msg);
t_protocol	fill_protocol(char *prefix, char *cmd, char **params, char *trailer);

/*
** cmd.c
*/
void	init_ptr_func(t_ptr_func *ptr_func);
void	cmd_unknown(t_env *e, int cs, t_protocol msg);
void	cmd_privmsg(t_env *e, int cs, t_protocol msg);
void	cmd_user(t_env *e, int cs, t_protocol msg);
void	cmd_nick(t_env *e, int cs, t_protocol msg);
void	cmd_ping(t_env *e, int cs, t_protocol msg);
void	register_client(t_fd *client);
void	cmd_away(t_env *e, int cs, t_protocol msg);

#endif /* !BIRCD_H_ */
