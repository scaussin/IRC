/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:27:54 by scaussin          #+#    #+#             */
/*   Updated: 2016/03/21 00:43:45 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/resource.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include "bircd.h"

int		main(int ac, char **av)
{
	t_env	e;

	init_env(&e);
	
	get_opt(&e, ac, av);
	srv_create(&e, e.port);
	main_loop(&e);

	/*test*/
	/*t_ring_buf buf;
	//buf.start = 6;
	print_buf(buf);
	write_buf(&buf, "bonjour132456", 7);
	print_buf(buf);
	write_buf(&buf, "1234", 4);
	print_buf(buf);*/
	return (0);
}

void	print_buf(t_ring_buf buf)
{
	char	*data_buf;

	data_buf = read_buf(buf);
	ft_printf("###########\n\
start: %d\n\
len:   %d\n\
data:  |%s|\n\n", buf.start, buf.len, data_buf);
	free (data_buf);
}

void	main_loop(t_env *e)
{
	while (1)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
	}
}

void	init_env(t_env *e)
{
	int		i;
	struct rlimit	rlp;

	X(-1, getrlimit(RLIMIT_NOFILE, &rlp), "getrlimit");
	e->maxfd = rlp.rlim_cur;
	e->fds = (t_fd*)Xv(NULL, malloc(sizeof(*e->fds) * e->maxfd), "malloc");
	i = 0;
	while (i < e->maxfd)
	{
		clean_fd(&e->fds[i]);
		i++;
	}
}

void	get_opt(t_env *e, int ac, char **av)
{
	if (ac != 2)
	{
		fprintf(stderr, USAGE, av[0]);
		exit(1);
	}
	e->port = atoi(av[1]);
}

void	srv_create(t_env *e, int port)
{
	int					s;
	struct sockaddr_in	sin;
	struct protoent		*pe;
	
	pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), "getprotobyname");
	s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket");
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(port);
	X(-1, bind(s, (struct sockaddr*)&sin, sizeof(sin)), "bind");
	X(-1, listen(s, 42), "listen");
	e->fds[s].type = FD_SERV;
	e->fds[s].fct_read = srv_accept;
}