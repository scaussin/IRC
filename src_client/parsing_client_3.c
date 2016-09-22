/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_client_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 09:55:21 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/21 09:55:31 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

void	send_cmd_msg(t_client *e, t_parsing_client *msg)
{
	char	*esp;

	esp = ft_strchr(msg->data, ' ');
	if (esp && esp[1])
	{
		*esp = 0;
		send_privmsg(e, msg->data, &esp[1]);
	}
	else
		write_log("warning", "usage : /msg <pseudo> <msg>");
}
