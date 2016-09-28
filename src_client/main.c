/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 13:33:51 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/28 14:08:12 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

int		main(int ac, char **av)
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
	int i;

	i = 0;
	while (i < 5)
	{
		init_fd(e);
		do_select(e);
		check_fd(e);
		if (e->socket == -1)
			ft_printf("usage : /connect <ip> <port>\n");
	}
}

void	init_client(t_client *e)
{
	if (e->chan)
		free(e->chan);
	if (e->host)
		free(e->host);
	if (e->func_client)
		free(e->func_client);
	if (e->func_server)
		free(e->func_server);
	bzero(e, sizeof(t_client));
	e->socket = -1;
	e->func_client = XV(NULL,
		malloc(NBPTRFUNCCLIENT * sizeof(t_func_client)), "malloc");
	init_ptr_func_client(e->func_client);
	e->func_server = XV(NULL,
		malloc(NBPTRFUNCSERVER * sizeof(t_func_server)), "malloc");
	init_ptr_func_server(e->func_server);
}

void	init_ptr_func_client(t_func_client *func_client)
{
	func_client[0].name = "/msg";
	func_client[0].func = send_cmd_msg;
	func_client[1].name = "/leave";
	func_client[1].func = cmd_leave_client;
	func_client[2].name = "/connect";
	func_client[2].func = cmd_connect;
	func_client[3].name = "/disconnect";
	func_client[3].func = cmd_disconnect;
	func_client[4].name = "/quit";
	func_client[4].func = cmd_quit;
	func_client[5].name = "/who";
	func_client[5].func = send_cmd_who;
}

void	init_ptr_func_server(t_func_server *func_server)
{
	func_server[0].name = "PRIVMSG";
	func_server[0].func = cmd_privmsg_server;
	func_server[1].name = "JOIN";
	func_server[1].func = cmd_join_server;
	func_server[2].name = "PART";
	func_server[2].func = cmd_part_server;
	func_server[3].name = "353";
	func_server[3].func = cmd_names_server;
	func_server[4].name = "366";
	func_server[4].func = cmd_end_names_server;
	func_server[5].name = "QUIT";
	func_server[5].func = cmd_quit_server;
	func_server[6].name = "433";
	func_server[6].func = cmd_nick_server;
	func_server[7].name = "462";
	func_server[7].func = cmd_already_registered_server;
	func_server[8].name = "322";
	func_server[8].func = cmd_list_server;
	func_server[9].name = "321";
	func_server[9].func = cmd_start_end_list_server;
	func_server[10].name = "323";
	func_server[10].func = cmd_start_end_list_server;
}
