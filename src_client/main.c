/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:33:51 by scaussin          #+#    #+#             */
/*   Updated: 2016/06/03 18:57:56 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

int main(int ac, char **av)
{
	t_client	e;

	init_client(&e);
	if (ac == 3)
		connect_to_srv(&e, av[1], ft_atoi(av[2]));
	main_loop(&e);
	return (0);
}

void	main_loop(t_client *e)
{
	int i = 0;
	while (i < 5)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
		//i++;
	}
}

void	init_client(t_client *e)
{
	bzero(e, sizeof(t_client));
	e->socket = -1;
	e->chan = NULL;
	e->func_client = Xv(NULL,
		malloc(NB_PTR_FUNC_CLIENT * sizeof(t_func_client)), "malloc");
	init_ptr_func_client(e->func_client);
	e->func_server = Xv(NULL,
		malloc(NB_PTR_FUNC_SERVER * sizeof(t_func_server)), "malloc");
	init_ptr_func_server(e->func_server);
}

void	init_ptr_func_client(t_func_client *func_client)
{
	func_client[0].name = "/msg";
	func_client[0].func = send_cmd_msg;
	func_client[1].name = "/leave";
	func_client[1].func = cmd_leave_client;
	func_client[2].name = "/connect";
	func_client[2].func = NULL;
}

void	init_ptr_func_server(t_func_server *func_server)
{
	func_server[0].name = "PRIVMSG";
	func_server[0].func = cmd_privmsg_server;
}
