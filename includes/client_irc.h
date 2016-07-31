/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_irc.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 12:11:39 by scaussin          #+#    #+#             */
/*   Updated: 2016/07/31 23:08:01 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_IRC_H_
# define CLIENT_IRC_H_


# include "libft.h"

# define END					"\r\n"
# define MAX_LEN_NICK			9
# define BUF_SIZE				4096
# define MAX_SIZE_MSG_IRC		512
# define NB_PTR_FUNC_CLIENT		6
# define NB_PTR_FUNC_SERVER		8


# define Xv(err,res,str)	(x_void(err,res,str,__FILE__,__LINE__))
# define X(err,res,str)		(x_int(err,res,str,__FILE__,__LINE__))
# define MAX(a,b)	((a > b) ? a : b)
# define MIN(a,b)	((a < b) ? a : b)

typedef struct	s_ring_buf
{
	int			start;
	int			len;
	char		data[BUF_SIZE];
}				t_ring_buf;

typedef struct	s_protocol
{
	char		*prefix;
	char		*command;
	char		**params;
	char		*trailer;
}				t_protocol;

typedef struct	s_parsing_client
{
	char		*command;
	char		*data;
}				t_parsing_client;

typedef struct	s_client
{
	int			ret_select;
	int			max_select;
	int			socket;
	char		leaving;
	char		*host;
	fd_set		fd_read;
	fd_set		fd_write;
	struct s_c	*func_client;
	struct s_s	*func_server;
	char		nick[MAX_LEN_NICK + 1];
	char		*chan;
	t_ring_buf	buf_read_client;
	t_ring_buf	buf_write_client;
	t_ring_buf	buf_read_server;
	t_ring_buf	buf_write_server;
}				t_client;

typedef struct	s_c
{
	char		*name;
	void		(*func)(t_client *e, t_parsing_client *msg);
}				t_func_client;

typedef struct	s_s
{
	char		*name;
	void		(*func)(t_client *e, t_protocol *msg);
}				t_func_server;

/*
** main.c
*/
void	main_loop(t_client *e);
void	init_client(t_client *e);
void	init_ptr_func_client(t_func_client *func_client);
void	init_ptr_func_server(t_func_server *func_server);

/*
** read.c
*/
int		read_circular(t_ring_buf *buf_read, int cs);
void	read_server(t_client *e, int cs);
void	read_client(t_client *e, int cs);

/*
** write.c
*/
void	send_server(t_ring_buf *buf, int cs);
void	write_server(t_client *e, int cs);
void	write_client(t_client *e, int cs);
void	send_protocol_to_server(t_client *e, t_protocol msg);

/*
** connect.c
*/
int		connect_to_srv(t_client *e, char *addr, int port);
void	auth_irc(t_client *e);
void	close_connection(t_client *e);

/*
** select.c
*/
void	init_fd(t_client *e);
void	do_select(t_client *e);
void	check_fd(t_client *e);

/*
** buf.c
*/
void	write_buf(t_ring_buf *buf, char *to_write, int size);
char	*read_buf(t_ring_buf buf);
void	update_offset_buf(t_ring_buf *buf, int new_offset);


/*
** lexer_server.c
*/
int		lexer_server(t_protocol *msg, t_ring_buf *buf);
int		check_error(char *line, char **end, t_ring_buf *buf);
int		extract_prefix(char **prefix, char **msg);
int		extract_command(char **command, char **msg);
int		extract_params(char ***params, char **msg);
int		extract_trailer(char **trailer, char **msg);
/*
** tools.c
*/
int		x_int(int err, int res, char *str, char *file, int line);
void	*x_void(void *err, void *res, char *str, char *file, int line);
void	write_log(char *type_error, char *msg);
int		str_isalnum(char *str);
void	free_parsing_client(t_parsing_client *msg);
int		str_equal(char *s1, char *s2);

/*
** parsing_client.c
*/
void	parser_client(t_client *e, t_parsing_client *msg);
int		manage_nick(t_client *e, t_parsing_client *msg);
void	cmd_privmsg_client(t_client *e, t_parsing_client *msg);
void	send_cmd_msg(t_client *e, t_parsing_client *msg);
void	send_privmsg(t_client *e, char *to, char *msg);
void	send_row_cmd_client(t_client *e, t_parsing_client *msg);
void	cmd_leave_client(t_client *e, t_parsing_client *msg);
void	send_cmd_who(t_client *e, t_parsing_client *msg);
void	cmd_connect(t_client *e, t_parsing_client *msg);
void	cmd_disconnect(t_client *e, t_parsing_client *msg);
void	cmd_quit(t_client *e, t_parsing_client *msg);

/*
** lexer_client.c
*/
int		lexer_client(t_client *e, t_parsing_client *msg);
int		extract_cmd_client(char **str, t_parsing_client *msg);
int		extract_data_client(char *str, t_parsing_client *msg);

/*
** protocol.c
*/
char	*protocol_to_string(t_protocol msg);
void	print_protocol(t_protocol msg);
t_protocol	fill_protocol(char *prefix, char *cmd, char **params, char *trailer);
void	free_params(char **params);
char	**malloc_params(int size);
void	free_protocol(t_protocol msg);

/*
** parsing_server.c
*/
void	parsing_server(t_client *e, t_protocol *msg);
void	cmd_server_unknown(t_protocol *msg);
void	cmd_privmsg_server(t_client *e, t_protocol *msg);
char	*extract_nick_prefix(char *prefix);
char	*formate_origin_privmsg(t_protocol *msg);
void	cmd_join_server(t_client *e, t_protocol *msg);
void	cmd_part_server(t_client *e, t_protocol *msg);
void	cmd_end_names_server(t_client *e, t_protocol *msg);
void	cmd_names_server(t_client *e, t_protocol *msg);
void	cmd_quit_server(t_client *e, t_protocol *msg);
void	cmd_nick_server(t_client *e, t_protocol *msg);
void	cmd_already_registered_server(t_client *e, t_protocol *msg);

#endif /* !CLIENT_IRC_H_ */
